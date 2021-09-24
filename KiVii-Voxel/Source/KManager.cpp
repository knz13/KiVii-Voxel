#include "KManager.h"
#include "RenderWindow.h"
#include "CubeVoxel.h"
#include "Camera.h"

RenderWindow* KManager::m_CurrentWindow = nullptr;
GLFWwindow* KManager::m_CurrentGLFWwindowPointer = nullptr;
unordered_map<int, CubeVoxel*> KManager::m_Cubes;
unordered_map<int, Camera*> KManager::m_Cameras;
queue<int> KManager::m_IDsToDelete;
queue<CubeVoxel*> KManager::m_CubesNotInUse;
OctreeNode* KManager::m_OctreeHeadNode = nullptr;

bool KManager::FrustrumCulling(Vector3f pos)
{
	Vector4f posInCam = m_CurrentWindow->GetProjection() * m_CurrentWindow->GetView() * Vector4f(pos, 1.0f);
	Vector3f posInCameraSpace = Vector3f(posInCam.x, posInCam.y, posInCam.z) / posInCam.w;

	if (posInCameraSpace.x < - 1.2 || posInCameraSpace.x > 1.2) {
		return false;
	}
	else {
		if (posInCameraSpace.y < -1.2 || posInCameraSpace.y > 1.2) {
			return false;
		}
		else {
			if (posInCameraSpace.z < -1.2 || posInCameraSpace.z > 1.2) {
				return false;
			}
			else {
				return true;
			}
		}
	}

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
	m_OctreeHeadNode = new OctreeNode(STARTING_NODE_SIZE, Vector3i(0, STARTING_NODE_SIZE / 2, 0));
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
	m_OctreeHeadNode = m_OctreeHeadNode->GetHeadNode();

	m_OctreeHeadNode->StartCleanup();

	delete m_OctreeHeadNode;

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

void KManager::UpdateCubes()
{
	m_OctreeHeadNode = m_OctreeHeadNode->GetHeadNode();

	while (m_IDsToDelete.size() != 0) {
		m_CubesNotInUse.push(m_Cubes[m_IDsToDelete.front()]);
		m_Cubes.erase(m_IDsToDelete.front());
		m_IDsToDelete.pop();
	}
	vector<glm::mat4> matrices;
	vector<Vector3f> colors;
	colors.reserve(m_Cubes.size());
	matrices.reserve(m_Cubes.size());

	if (m_CubesNotInUse.size() > 1000) {
		delete m_CubesNotInUse.front();
		m_CubesNotInUse.pop();
	}
	
	//cout << Vector3f(m_CurrentWindow->GetView() * Vector4f(m_Cubes[0]->GetPosition(), 1.0f)).x << endl;

	unsigned int index = 0;
	for (auto& cube : m_Cubes) {
		if (FrustrumCulling(cube.second->GetPositionInWorldSpace())) {
			cube.second->SetupForDrawing(index);
			colors.push_back(cube.second->GetColor());
			matrices.push_back(cube.second->GetModelMatrix());
			index++;
		}
	}
	if (matrices.size() > 0) {
		m_CurrentWindow->DrawInstances((int)matrices.size(), &matrices,&colors);
	}
}

