#pragma once
#include "GL_CALL.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "KTexture.h"
#include "Shader.h"

class ScreenQuad {

private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	VertexBufferLayout m_VBL;
	Shader m_Shader;
	KTexture m_Texture;

public:
	ScreenQuad();

	KTexture& GetTexture();
	Shader& GetShader() { return m_Shader; };
	VertexArray& GetVertexArray() { return m_VAO; };
	void UpdateSize(int x, int y);
	void Bind();
	void Init();
};
