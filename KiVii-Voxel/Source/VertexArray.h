#pragma once
#include "GL_CALL.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {

private:
	unsigned int m_RendererID;
	unsigned int m_indexOffset = 0;
	unsigned int m_cummulativeOffset = 0;

	
	
	friend class KManager;
public:
	VertexArray();
	~VertexArray() {};

	void Init();
	void AddBuffer(VertexBuffer& vb, VertexBufferLayout vbl);

	void SetCummulativeOffset(unsigned int stride) { m_cummulativeOffset = stride; };
	unsigned int GetCummulativeOffset() { return m_cummulativeOffset; };

	void SetIndexOffset(unsigned int offset) { m_indexOffset = offset; };
	unsigned int GetIndexOffset() { return m_indexOffset; };
	void Bind();
	void Unbind();

};