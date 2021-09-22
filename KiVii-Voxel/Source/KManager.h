#pragma once
#include "GuiManager.h"

class RenderWindow;
class Camera;
class CubeVoxel;
class KManager {
	
private:
	static RenderWindow* m_CurrentWindow;
	static GLFWwindow* m_CurrentGLFWwindowPointer;
	static unordered_map<int,CubeVoxel*> m_Cubes;
	static unordered_map<int, Camera*> m_Cameras;

	static queue<int> m_IDsToDelete;
	static queue<CubeVoxel*> m_CubesNotInUse;
	

public:
	static GLFWwindow*& Init(RenderWindow* win);
	static void InitGui();
	static void Cleanup();

	static void AddCamera(Camera* camera);

	static CubeVoxel* GenVoxel();
	static void AddCube(CubeVoxel* cube);
	static void DeleteCube(CubeVoxel* cube);

	static float GetDeltaTime();

	static void UpdateCubes();

	static RenderWindow* GetWindow() { return m_CurrentWindow; };
	static GLFWwindow* GetGLFWwindowPointer() { return m_CurrentGLFWwindowPointer; };
	static const unordered_map<int,CubeVoxel*>& GetCubes() { return m_Cubes; };

};
