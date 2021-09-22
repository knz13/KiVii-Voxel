#include "RenderTarget.h"
#include "RenderWindow.h"

RenderWindow* RenderTarget::win;
Shader RenderTarget::m_Shader;
VertexBuffer RenderTarget::m_VBO;
VertexArray RenderTarget::m_VAO;
VertexBufferLayout RenderTarget::m_VBL;
IndexBuffer RenderTarget::m_IB;
void RenderTarget::SetupVertexArray()
{
	m_VAO.AddBuffer(m_VBO, m_VBL);
}

void RenderTarget::BindBuffers()
{
	m_Shader.Bind();
	m_VAO.Bind();
	m_VBO.Bind();
	m_IB.Bind();
}

void RenderTarget::Init()
{
	ASSERTWITHMSG(KManager::GetGLFWwindowPointer() != nullptr, "Window Not Defined!");
	win = KManager::GetWindow();
	m_Shader.GenerateDefaultShader();


	float vertices[] = {
		// front
	-0.1, -0.1,  0.1,
	 0.1, -0.1,  0.1,
	 0.1,  0.1,  0.1,
	-0.1,  0.1,  0.1,
	// back
	-0.1, -0.1, -0.1,
	 0.1, -0.1, -0.1,
	 0.1,  0.1, -0.1,
	-0.1,  0.1, -0.1
	};
	float indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	m_VBO.CreateBuffer(vertices, 24);
	m_IB.CreateBuffer(indices, 36);
	m_VBL.Push<float>(3);
	m_VAO.AddBuffer(m_VBO, m_VBL);
}

RenderTarget::RenderTarget()
{
	
}

RenderTarget::~RenderTarget()
{
}


