

#include <iostream>
#include "RenderWindow.h"
#include "KManager.h"
#include "CubeVoxel.h"
#include "Camera.h"
#include "OctreeNode.h"
#include "ScreenQuad.h"
#include "ComputeShader.h"
#include "ShaderStorageBuffer.h"
#include "KTexture.h"

using namespace std;


int main() {

	RenderWindow win(Vector2f(1280, 720), "hello!");

	ScreenQuad quad;
	vector<float> renderData;
	ComputeShader rayMarchingShader,gpuOctreeBegin,gpuOctreeFill;
	ShaderStorageBuffer voxelsToRenderBuffer;

	quad.Init();
	quad.GetTexture().Init2D(win.GetSize().x, win.GetSize().y, nullptr, GL_RGBA8, 0, GL_RGBA);
	voxelsToRenderBuffer.Init();
	rayMarchingShader.Init();

	rayMarchingShader.GenerateShader("RayTracing Shader");



	for (int y = 0; y < 3;y++) {
		for (int z = 0; z < 3; z++) {
			for (int x = 0; x < 3; x++) {
				CubeVoxel* cube = KManager::GenVoxel();
				cube->SetPosition(x*2, y*2,-20 + z*2);
				cube->SetColor(Color(255 - x * 10, 255 - y * 10, 255 - z * 10));
			}
		}
	}


	
	
	CubeVoxel* myCube = KManager::GenVoxel();

	myCube->SetColor(Color::Red);
	myCube->SetPosition(3, 2, 7);
	
	win.GetMainCamera()->SetPosition(3, 5, 2);

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

		


		KManager::BeginFrame();


		if (renderData.size() != 0) {

			rayMarchingShader.Bind();
			rayMarchingShader.SetUniform3f("cameraPos", win.GetMainCamera()->GetPosition());
			rayMarchingShader.SetUniform1f("cameraNear", win.GetRenderNearCutOff());
			rayMarchingShader.SetUniform1f("cameraFar", win.GetRenderDistance());
			rayMarchingShader.SetUniformMat4f("cameraInvViewProj", win.GetMainCamera()->GetInvViewProjMat());
			rayMarchingShader.SetUniform1f("boxSize", VOXEL_ENTITY_SIZE / 2);

			quad.GetTexture().Bind(1);
			quad.GetTexture().BindImageTexture(1, GL_READ_WRITE, GL_RGBA8);
			voxelsToRenderBuffer.CreateBuffer(renderData.data(), renderData.size() * sizeof(float), GL_DYNAMIC_COPY);
			voxelsToRenderBuffer.SetBinding(0);

			rayMarchingShader.Dispatch(win.GetSize().x, win.GetSize().y, 1);


		}



		renderData.clear();
		KManager::GetObjectsInView(renderData);


		rayMarchingShader.Join();
		quad.Bind();
		quad.GetShader().Bind();
		quad.GetTexture().Bind(0);
		quad.GetShader().SetUniform1i("tex0", 0);
		win.DrawCurrentBoundNoIB(6, GL_TRIANGLES);


		KManager::EndFrame();
		KManager::BeginGUI();

		ImGui::BulletText(("Number Of Objects: " + to_string(renderData.size())).c_str());

		KManager::EndGUI();
		

		win.SwapBuffers();
	}

}