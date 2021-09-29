

#include <iostream>
#include "RenderWindow.h"
#include "KManager.h"
#include "CubeVoxel.h"
#include "Camera.h"



using namespace std;


int main() {

	RenderWindow win(Vector2f(1280, 720), "hello!");



	
		
	for (int j = 0; j < 100; j++) {
		for (int i = 0; i < 500; i++) {
				CubeVoxel* cube = KManager::GenVoxel();
				cube->SetPosition(-50 + i * 2, j*2, -20);
				cube->SetColor(Color::Blue);
		}
	}
		
	
	
	
	
	CubeVoxel* myCube = KManager::GenVoxel();

	myCube->SetColor(Color::Red);
	myCube->SetPosition(-20, 0, 64);


	while (win.isOpen()) {


		if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_UP) == GLFW_PRESS) {
			myCube->Move(0, 0, -1);
		}
		else if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_DOWN) == GLFW_PRESS) {
			myCube->Move(0, 0, 1);
		}
		else if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
			myCube->Move(1, 0, 0);
		}
		else if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_LEFT) == GLFW_PRESS) {
			myCube->Move(-1, 0, 0);
		}
		else if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_K) == GLFW_PRESS) {
			myCube->Move(0, 2, 0);
		}
		else if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_L) == GLFW_PRESS) {
			myCube->Move(0, -2, 0);
		}

		//win.GetMainCamera()->CheckIfPointInFrustrum(KManager::GetVoxelPosInWorldSpace(myCube->GetPosition()));


		win.Clear();


		KManager::UpdateCubes();

		

		win.SwapBuffers();
	}

}