#include "KManager.h"
#include "RenderWindow.h"
#include "GuiManager.h"
#include "CubeVoxel.h"
#include "OctreeNode.h"
#include "Camera.h"
#include "ScreenQuad.h"
#include "ComputeShader.h"

RenderWindow* KManager::m_CurrentWindow = nullptr;
GLFWwindow* KManager::m_CurrentGLFWwindowPointer = nullptr;
unordered_map<int, CubeVoxel*> KManager::m_Cubes;
unordered_map<int, Camera*> KManager::m_Cameras;
queue<int> KManager::m_IDsToDelete;
queue<CubeVoxel*> KManager::m_CubesNotInUse;
OctreeNode<CubeVoxel>* KManager::m_OctreeHead = nullptr;
vector<KDrawData> KManager::RenderData;
ComputeShader KManager::m_ComputeShader;
ScreenQuad KManager::m_ScreenQuad;

void KManager::DrawGui()
{
	GuiManager::Begin();

	
	ImGui::Begin("Hello!");
	
	
	if (ImGui::GetMousePos().x >= ImGui::GetWindowPos().x && ImGui::GetMousePos().x <= ImGui::GetWindowPos().x + ImGui::GetWindowSize().x) {
		if (ImGui::GetMousePos().y >= ImGui::GetWindowPos().y && ImGui::GetMousePos().y <= ImGui::GetWindowPos().y + ImGui::GetWindowSize().y)
		{
			m_CurrentWindow->GetMainCamera()->StopMoving();
		}
	}
	ImGui::BulletText(("Camera Pos: " + GetVec3AsString(m_CurrentWindow->GetMainCamera()->GetPosition())).c_str());
	ImGui::InputFloat("Camera Speed", &m_CurrentWindow->GetMainCamera()->m_MovingSpeed);
	ImGui::BulletText(("Framerate: " + to_string((int)(1/m_CurrentWindow->m_DeltaTime))).c_str());
	ImGui::BulletText(("Number Of Objects On Screen: " + to_string(RenderData.size())).c_str());

	ImGui::BulletText("Fov");
	ImGui::SameLine();
	
	if (ImGui::SliderFloat("##323125", &m_CurrentWindow->GetMainCamera()->m_Fov, 0.0f, 100.0f)) {
		m_CurrentWindow->SetMainCamera(m_CurrentWindow->GetMainCamera());
	}

	ImGui::BulletText("Fov Cutoff");
	ImGui::SameLine();
	ImGui::SliderFloat("##2321", &m_CurrentWindow->GetMainCamera()->m_Frustrum.frustrumFovIncrease, -m_CurrentWindow->GetMainCamera()->GetFov() + 1, 50.0f);


	ImGui::BulletText("Draw Distance");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##231", &m_CurrentWindow->m_Properties.farClipping, 10.0f, 300.0f)) {
		m_CurrentWindow->SetMainCamera(m_CurrentWindow->GetMainCamera());
	}


	ImGui::End();



	GuiManager::End();

	//m_CurrentWindow->GetMainCamera()->StartMoving();
}

GLFWwindow*& KManager::Init(RenderWindow* win)
{
	m_CurrentWindow = win;
	return m_CurrentGLFWwindowPointer;
}

void KManager::InitGui()
{
	ASSERT(m_CurrentGLFWwindowPointer != nullptr);
	GuiManager::Init();
	CubeVoxel::GetIndexBuffer().Init();
	CubeVoxel::GetVertexBuffer().Init();
	CubeVoxel::GetVertexArray().Init();
	CubeVoxel::GetShader().GenerateDefaultShader();
	RenderTarget::Init();
	m_ScreenQuad.Init();
	m_ComputeShader.Init();
	m_ComputeShader.GenerateShader("RayTracing Shader");
	m_OctreeHead = new OctreeNode<CubeVoxel>(Vector3i(0, STARTING_NODE_SIZE/2, 0), STARTING_NODE_SIZE);
}

void KManager::Cleanup()
{
	if (GuiManager::m_IO != nullptr) {
		GuiManager::Cleanup();
	}

	for (auto& cube : m_Cubes) {
		delete cube.second;
	}
	for (auto& camera : m_Cameras) {
		delete camera.second;
	}
	
	if (m_OctreeHead != nullptr) {



		delete m_OctreeHead;
	}

}

void KManager::AddCamera(Camera* camera)
{
	static int ID = 0;
	camera->m_ID = ID;
	m_Cameras[ID] = camera;
	ID++;
}

CubeVoxel* KManager::GenVoxel()
{
	if (m_CubesNotInUse.size() != 0) {
		CubeVoxel* cube = m_CubesNotInUse.front();
		cube->Reset();
		m_CubesNotInUse.pop();

		return cube;

	} 
	else {
		CubeVoxel* cube = new CubeVoxel();

		return cube;
	}
	
}

void KManager::AddCube(CubeVoxel* cube)
{
	static int ID = 0;
	cube->m_ID = ID;
	m_Cubes[ID] = cube;
	ID++;

}

void KManager::DeleteCube(CubeVoxel* cube)
{
	if (cube->m_IsRendered) {
		GetOctree()->RemoveInformation(cube->GetPosition());
	}
	m_IDsToDelete.push(cube->m_ID);
	
}

float KManager::GetDeltaTime()
{
	return m_CurrentWindow->m_DeltaTime;
}

OctreeNode<CubeVoxel>* KManager::GetOctree()
{
	m_OctreeHead = m_OctreeHead->GetHeadNode();
	return m_OctreeHead;
}

void KManager::UpdateCubes()
{
	RenderData.clear();
	m_CurrentWindow->GetMainCamera()->StartMoving();
	

	while (m_IDsToDelete.size() != 0) {
		CubeVoxel* cube = m_Cubes[m_IDsToDelete.front()];
		m_CubesNotInUse.push(cube);
		m_Cubes.erase(m_IDsToDelete.front());
		m_IDsToDelete.pop();
	}

	//m_CurrentWindow->GetMainCamera()->SetPosition(3, 2, 7);

	m_ComputeShader.Bind();
	m_ComputeShader.SetUniform3f("eyePos", m_CurrentWindow->GetMainCamera()->GetPosition());

	Vector4f ray00, ray01, ray10, ray11;
		
	ray00 = Vector4f(m_CurrentWindow->GetMainCamera()->m_Frustrum.inverseViewProjMat * Vector4f(-1, -1, 0, 1));
	ray10 = Vector4f(m_CurrentWindow->GetMainCamera()->m_Frustrum.inverseViewProjMat*Vector4f(1,-1,0,1));
	ray01 = Vector4f(m_CurrentWindow->GetMainCamera()->m_Frustrum.inverseViewProjMat*Vector4f(-1,1,0,1));
	ray11 = Vector4f(m_CurrentWindow->GetMainCamera()->m_Frustrum.inverseViewProjMat*Vector4f(1,1,0,1));

	ray00 /= ray00.w;
	ray10 /= ray10.w;
	ray01 /= ray01.w;
	ray11 /= ray11.w;

	ray00 -= Vector4f(m_CurrentWindow->GetMainCamera()->GetPosition(),1.0f);
	ray10 -= Vector4f(m_CurrentWindow->GetMainCamera()->GetPosition(),1.0f);
	ray01 -= Vector4f(m_CurrentWindow->GetMainCamera()->GetPosition(),1.0f);
	ray11 -= Vector4f(m_CurrentWindow->GetMainCamera()->GetPosition(),1.0f);

	m_ComputeShader.SetUniform3f("ray00", ray00);
	m_ComputeShader.SetUniform3f("ray10", ray10);
	m_ComputeShader.SetUniform3f("ray01", ray01);
	m_ComputeShader.SetUniform3f("ray11", ray11);




	m_ScreenQuad.GetTexture().Init(GL_TEXTURE_2D, m_CurrentWindow->GetSize().x, m_CurrentWindow->GetSize().y,nullptr,GL_RGBA8);
	m_ScreenQuad.GetTexture().BindImageTexture(0, GL_WRITE_ONLY, GL_RGBA8);
	m_ComputeShader.Dispatch(m_CurrentWindow->GetSize().x, m_CurrentWindow->GetSize().y, 1);
	

	
	

	//KManager::GetOctree()->GetObjectsInView(std::bind(&Camera::IsVoxelInFrustrum, m_CurrentWindow->GetMainCamera(),std::placeholders::_1,std::placeholders::_2), RenderData);


	if (m_CubesNotInUse.size() > 1000) {
		delete m_CubesNotInUse.front();
		m_CubesNotInUse.pop();
	}

	
	m_ComputeShader.Join();
	m_ScreenQuad.Bind();
	m_ScreenQuad.GetShader().Bind();
	m_ScreenQuad.GetTexture().Bind(0);
	m_ScreenQuad.GetShader().SetUniform1i("tex0", 0);
	
	m_CurrentWindow->DrawCurrentBoundNoIB(6,GL_TRIANGLES);
	/*
	if (RenderData.size() > 0) {
		m_CurrentWindow->DrawInstances(RenderData.size(), RenderData);
	}
	*/


	DrawGui();
}

Vector3f KManager::GetVoxelPosInWorldSpace(Vector3i pos)
{
	return Vector3f(pos) * VOXEL_ENTITY_SIZE;
}

Vector3i KManager::GetWorldPosInVoxelSpace(Vector3f pos)
{
	return pos / VOXEL_ENTITY_SIZE;
}

