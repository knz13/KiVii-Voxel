#include "RenderWindow.h"
#include "CubeVoxel.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Camera.h"
#include "IndexBuffer.h"

RenderWindow::RenderWindow(Vector2f vec, string title)
	:m_Properties({vec,0.01f,300.0f,glm::perspective(glm::radians(45.0f),vec.x/vec.y,0.01f,300.0f)})
{
	

	ASSERTWITHMSG(glfwInit(), "glfw not Initiated.");

	KManager::Init(this) = glfwCreateWindow((int)vec.x, (int)vec.y, title.c_str(), NULL, NULL);
	
	
	

	glfwMakeContextCurrent(KManager::GetGLFWwindowPointer());

	
	
	ASSERTWITHMSG(glewInit() == GLEW_OK, "glew not Initiated.");

	cout << glewGetString(GLEW_VERSION) << endl;
	
	KManager::InitGui();

	this->SetMainCamera(new Camera());

}


RenderWindow::~RenderWindow()
{
}

void RenderWindow::DrawInstances(vector<glm::mat4>& modelMatrices, int instanceCount)
{
	CubeVoxel::BindBuffers();
	unsigned int id = CubeVoxel::GetVertexBufferID();
	unsigned int transform_vbo;
	glGenBuffers(1, &transform_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, transform_vbo);
	GL_CALL(glBufferData(GL_ARRAY_BUFFER,sizeof(glm::mat4)*modelMatrices.size(),&modelMatrices[0],GL_STATIC_DRAW));

	for (int i = CubeVoxel::GetLayout().GetCount(); i < CubeVoxel::GetLayout().GetCount() + 4; i++) {
		GL_CALL(glEnableVertexAttribArray(i));
		GL_CALL(glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),(const void*)(sizeof(float) * ((i - CubeVoxel::GetLayout().GetCount()) * 4))));
		GL_CALL(glVertexAttribDivisor(i, 1));
	}

	GL_CALL(glDrawElementsInstanced(GL_TRIANGLES, CubeVoxel::GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, 0, instanceCount));
}

void RenderWindow::SetMainCamera(Camera* camera)
{
	m_Properties.projectionMatrix = glm::perspective(glm::radians(camera->GetFov()), m_Properties.size.x / m_Properties.size.y, m_Properties.nearClipping, m_Properties.farClipping);
	m_MainCamera = camera;
}

bool RenderWindow::isOpen()
{
	return !glfwWindowShouldClose(KManager::GetGLFWwindowPointer());
}

glm::mat4 RenderWindow::GetProjection()
{
	return m_Properties.projectionMatrix;
}

glm::mat4 RenderWindow::GetView()
{
	return m_MainCamera->GetView();
}

void RenderWindow::SwapBuffers()
{
	glfwSwapBuffers(KManager::GetGLFWwindowPointer());
}

void RenderWindow::Clear()
{
	currentTime = glfwGetTime();
	m_DeltaTime = (float)(currentTime - lastTime);
	lastTime = currentTime;

	glfwPollEvents();
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}
