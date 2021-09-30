#include "KManager.h"
#include "RenderWindow.h"
#include "GuiManager.h"
#include "CubeVoxel.h"
#include "OctreeNode.h"
#include "Camera.h"

RenderWindow* KManager::m_CurrentWindow = nullptr;
GLFWwindow* KManager::m_CurrentGLFWwindowPointer = nullptr;
unordered_map<int, CubeVoxel*> KManager::m_Cubes;
unordered_map<int, Camera*> KManager::m_Cameras;
queue<int> KManager::m_IDsToDelete;
queue<CubeVoxel*> KManager::m_CubesNotInUse;
OctreeNode<CubeVoxel>* KManager::m_OctreeHead = nullptr;
vector<CubeVoxel*> KManager::voxelsToRender;


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
	ImGui::BulletText(("Framerate: " + to_string(1/m_CurrentWindow->m_DeltaTime)).c_str());
	ImGui::BulletText(("Number Of Objects On Screen: " + to_string(voxelsToRender.size())).c_str());
	ImGui::BulletText("Fov Change");
	ImGui::SameLine();
	ImGui::SliderFloat("##2321", &m_CurrentWindow->GetMainCamera()->m_Frustrum.frustrumFovIncrease, -m_CurrentWindow->GetMainCamera()->GetFov() + 1, 50.0f);


	ImGui::BulletText("Draw Distance");
	ImGui::SameLine();
	ImGui::SliderFloat("##231", &m_CurrentWindow->m_Properties.farClipping, 10.0f, 300.0f);


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
	voxelsToRender.clear();
	m_CurrentWindow->GetMainCamera()->StartMoving();
	m_OctreeHead = m_OctreeHead->GetHeadNode();

	while (m_IDsToDelete.size() != 0) {
		CubeVoxel* cube = m_Cubes[m_IDsToDelete.front()];
		m_CubesNotInUse.push(cube);
		m_Cubes.erase(m_IDsToDelete.front());
		m_IDsToDelete.pop();
	}

	

	m_OctreeHead->GetObjectsInView(std::bind(&Camera::IsVoxelInFrustrum, m_CurrentWindow->GetMainCamera(),std::placeholders::_1,std::placeholders::_2), voxelsToRender);

	for (auto& voxel : voxelsToRender) {
		
	}

	vector<glm::mat4> matrices;
	vector<Vector3f> colors;
	colors.reserve(m_Cubes.size());
	matrices.reserve(m_Cubes.size());

	if (m_CubesNotInUse.size() > 1000) {
		delete m_CubesNotInUse.front();
		m_CubesNotInUse.pop();
	}
	
	unsigned int index = 0;
	for (auto& cube : voxelsToRender) {
			cube->SetupForDrawing(index);
			colors.push_back(cube->GetColor());
			matrices.push_back(cube->GetModelMatrix());
			index++;
	}
	if (matrices.size() > 0) {
		m_CurrentWindow->DrawInstances((int)matrices.size(), &matrices,&colors);
	}



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

