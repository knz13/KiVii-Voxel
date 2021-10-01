#include "ScreenQuad.h"

ScreenQuad::ScreenQuad()
{
}

KTexture& ScreenQuad::GetTexture()
{
	return m_Texture;
}

void ScreenQuad::UpdateSize(int x, int y)
{
	float positions[] = {
		-1,1,
		1,1,
		1,-1,
		1,-1,
		-1,-1,
		-1,1

	};

	m_VBO.CreateBuffer(positions, 12);
	m_VBL.Push<float>(2);

	m_VAO.SetCummulativeOffset(0);
	m_VAO.AddBuffer(m_VBO, m_VBL);
}

void ScreenQuad::Bind()
{
	m_VAO.Bind();
	m_Shader.Bind();
}

void ScreenQuad::Init()
{
	m_VBO.Init();
	m_VAO.Init();
	m_Shader.GenerateShader("ScreenQuad Shader");
	this->UpdateSize(0, 0);
}
