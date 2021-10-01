#pragma once
#include "GL_CALL.h"
#include "OctreeNode.h"

class ScreenQuad;
class RenderWindow;
class VertexArray;
class Camera;
class CubeVoxel;
class ComputeShader;
class KManager {
	
private:
	static RenderWindow* m_CurrentWindow;
	static vector<KDrawData> RenderData;
	static GLFWwindow* m_CurrentGLFWwindowPointer;
	static unordered_map<int,CubeVoxel*> m_Cubes;
	static unordered_map<int, Camera*> m_Cameras;
	static OctreeNode<CubeVoxel>* m_OctreeHead;
	static queue<int> m_IDsToDelete;
	static queue<CubeVoxel*> m_CubesNotInUse;
	static ScreenQuad m_ScreenQuad;
	static ComputeShader m_ComputeShader;

	static void DrawGui();
	
public:
	static GLFWwindow*& Init(RenderWindow* win);
	static void InitGui();
	static void Cleanup();

	static void AddCamera(Camera* camera);

	static CubeVoxel* GenVoxel();

	
	
	static void AddCube(CubeVoxel* cube);
	static void DeleteCube(CubeVoxel* cube);

	static float GetDeltaTime();

	static OctreeNode<CubeVoxel>* GetOctree();
	static void UpdateCubes();
	static Vector3f GetVoxelPosInWorldSpace(Vector3i pos);
	static Vector3i GetWorldPosInVoxelSpace(Vector3f pos);
	static RenderWindow* GetWindow() { return m_CurrentWindow; };
	static GLFWwindow* GetGLFWwindowPointer() { return m_CurrentGLFWwindowPointer; };
	static const unordered_map<int,CubeVoxel*>& GetCubes() { return m_Cubes; };

};
