#pragma once
#include "GL_CALL.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {

private:
	unsigned int m_RendererID;

	void Init();
	
	friend class KManager;
public:
	VertexArray();
	~VertexArray() {};

	
	void AddBuffer(VertexBuffer& vb, VertexBufferLayout vbl);

	void Bind();
	void Unbind();

};