

#include <iostream>
#include "RenderWindow.h"
#include "KManager.h"
#include "CubeVoxel.h"



using namespace std;


int main() {

	RenderWindow win(Vector2f(1280, 720), "hello!");

	CubeVoxel* cube = KManager::GenVoxel();
	cube->SetScale(100.0f);
	cube->SetPosition(0, 0, -20);
	while (win.isOpen()) {



		win.Clear();


		KManager::UpdateCubes();

		win.SwapBuffers();
	}

}