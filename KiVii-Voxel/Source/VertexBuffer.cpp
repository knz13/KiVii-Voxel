#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
	:m_NumberOfElements(0),m_RendererID(0)
{
}

VertexBuffer::~VertexBuffer()
{

}

void VertexBuffer::Init()
{
	GL_CALL(glGenBuffers(1, &m_RendererID));
}

void VertexBuffer::CreateBuffer(const void* data, unsigned int count,GLenum DrawingMode)
{
	this->Bind();
	m_NumberOfElements = count;
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, count*sizeof(float),data, DrawingMode));
}

void VertexBuffer::Bind()
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind()
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
