

#include <iostream>
#include "RenderWindow.h"
#include "KManager.h"
#include "CubeVoxel.h"



using namespace std;


int main() {

	RenderWindow win(Vector2f(1280, 720), "hello!");

	for (int j = 0; j < 30;j++) {
		for (int i = 0; i < 100; i++) {
			CubeVoxel* cube = KManager::GenVoxel();
			cube->SetPosition(-50 + i/2.0f, j*1, -10);
			cube->SetColor(Color(243,14,105));
		}
	}


	while (win.isOpen()) {



		win.Clear();


		KManager::UpdateCubes();

		

		win.SwapBuffers();
	}

}