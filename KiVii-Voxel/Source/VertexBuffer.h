#pragma once
#include "GL_CALL.h"

class VertexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_NumberOfElements;

	void Init();
	friend class RenderTarget;
	friend class KManager;

public:
	VertexBuffer();
	~VertexBuffer();


	
	void CreateBuffer(const void* data, unsigned int count);

	void Bind();
	void Unbind();
	unsigned int GetCount() { return m_NumberOfElements; }
	unsigned int GetID() { return this->m_RendererID; }
};