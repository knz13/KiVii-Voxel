#include "RenderWindow.h"
#include "CubeVoxel.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Camera.h"
#include "IndexBuffer.h"

static void framebuffer_size_callback(GLFWwindow*, int width, int height) {
	glViewport(0, 0, width, height);
}
RenderWindow::RenderWindow(Vector2f vec, string title)
	:m_Properties({vec,0.01f,300.0f,glm::perspective(45.0f,vec.x/vec.y,0.001f,300.0f)})
{
	

	ASSERTWITHMSG(glfwInit(), "glfw not Initiated.");

	

	KManager::Init(this) = glfwCreateWindow((int)vec.x, (int)vec.y, title.c_str(), NULL, NULL);
	
	
	

	glfwMakeContextCurrent(KManager::GetGLFWwindowPointer());

	
	
	ASSERTWITHMSG(glewInit() == GLEW_OK, "glew not Initiated.\n");

	cout << glGetString(GL_VERSION) << endl;
	
	KManager::InitGui();

	this->SetMainCamera(new Camera());

	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glDepthFunc(GL_LESS));
	GL_CALL(glEnable(GL_CULL_FACE));

	
	glfwSetFramebufferSizeCallback(KManager::GetGLFWwindowPointer(), framebuffer_size_callback);

	m_DrawingVBO.Init();

}


RenderWindow::~RenderWindow()
{
}

void RenderWindow::DrawInstances(int instanceCount, vector<glm::mat4>* modelMatrices, vector<Vector3f>* colors)
{
	CubeVoxel::BindBuffers();
	m_DrawingVBO.Bind();
	m_DrawingVBO.CreateBuffer(modelMatrices->data(), 4*4*modelMatrices->size(), GL_DYNAMIC_DRAW);
	m_DrawingVBL.Push<glm::mat4>(1,true);

	
	unsigned int indexOffset = CubeVoxel::GetVertexArray().GetIndexOffset();

	if (colors != nullptr) {
		VertexBuffer m_ColorBuffer;
		VertexBufferLayout m_ColorBufferLayout;

		m_ColorBuffer.Init();

		m_ColorBuffer.CreateBuffer(colors->data(),3*colors->size());
		m_ColorBufferLayout.Push<float>(3,true);

		CubeVoxel::GetVertexArray().AddBuffer(m_ColorBuffer, m_ColorBufferLayout);

	}

	CubeVoxel::GetVertexArray().AddBuffer(m_DrawingVBO, m_DrawingVBL);
	
	
	GL_CALL(glDrawElementsInstanced(GL_TRIANGLES, CubeVoxel::GetIndexBuffer().GetCount(), GL_UNSIGNED_INT,0, instanceCount));

	
	CubeVoxel::GetVertexArray().SetIndexOffset(indexOffset);
	m_DrawingVBL.Reset();
	m_DrawingVBO.Reset();
}

void RenderWindow::SetMainCamera(Camera* camera)
{
	m_Properties.projectionMatrix = glm::perspective(glm::radians(camera->GetFov()) , m_Properties.size.x / m_Properties.size.y, m_Properties.nearClipping, m_Properties.farClipping);
	m_MainCamera = camera;
}

bool RenderWindow::isOpen()
{
	return !glfwWindowShouldClose(KManager::GetGLFWwindowPointer());
}

float RenderWindow::GetRenderDistance()
{
	return m_Properties.farClipping;
}

float RenderWindow::GetRenderNearCutOff()
{
	return m_Properties.nearClipping;
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

	if (m_MainCamera != nullptr) {
		m_MainCamera->Bind();
		m_MainCamera->Update();
		//cout << "Current camera direction: " << m_MainCamera->m_Direction.x << "," << m_MainCamera->m_Direction.y << "," << m_MainCamera->m_Direction.z << endl;
	}
	currentTime = glfwGetTime();
	m_DeltaTime = (float)(currentTime - lastTime);
	lastTime = currentTime;

	glfwPollEvents();
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT));
}

