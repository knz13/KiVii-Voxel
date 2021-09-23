#pragma once
#include "GL_CALL.h"

class VertexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_NumberOfElements;

	
	friend class RenderTarget;
	friend class KManager;

public:
	VertexBuffer();
	~VertexBuffer();


	void Init();
	void CreateBuffer(const void* data, unsigned int count,GLenum DrawingMode = GL_STATIC_DRAW);

	void Bind();
	void Reset() { m_NumberOfElements = 0; };
	void Unbind();
	unsigned int GetCount() { return m_NumberOfElements; }
	unsigned int GetID() { return this->m_RendererID; }
};