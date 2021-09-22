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
	vector<glm::mat4> matrices;
	matrices.reserve(m_Cubes.size());

	while (m_IDsToDelete.size() != 0) {
		m_CubesNotInUse.push(m_Cubes[m_IDsToDelete.front()]);
		m_Cubes.erase(m_IDsToDelete.front());
		m_IDsToDelete.pop();
	}

	

	for (auto& cube : m_Cubes) {
		matrices.push_back(cube.second->GetModelMatrix());
	}
	if (matrices.size() > 0) {
		m_CurrentWindow->DrawInstances(matrices, (int)m_Cubes.size());
	}
	matrices.clear();
}

