

#include <iostream>
#include "RenderWindow.h"
#include "KManager.h"
#include "CubeVoxel.h"
#include "Camera.h"



using namespace std;


int main() {

	RenderWindow win(Vector2f(1280, 720), "hello!");


	for (int y = 0; y < 5;y++) {
		for (int z = 0; z < 5; z++) {
			for (int x = 0; x < 5; x++) {
				CubeVoxel* cube = KManager::GenVoxel();
				cube->SetPosition(x*2, y*2,-10 + z*2);
				cube->SetColor(Color(255 - x * 10, 255 - y * 10, 255 - z * 10));
			}
		}
	}


	
	
	CubeVoxel* myCube = KManager::GenVoxel();

	myCube->SetColor(Color::Red);
	myCube->SetPosition(-20, 0, -20);


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

		

		win.Clear();


		KManager::UpdateCubes();

		

		win.SwapBuffers();
	}

}