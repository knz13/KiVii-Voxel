#include "IndexBuffer.h"

void IndexBuffer::Init()
{
	GL_CALL(glGenBuffers(1, &m_RendererID));
}

IndexBuffer::IndexBuffer()
	:m_Count(0)
{
	
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::CreateBuffer(void* data, unsigned int count)
{
	this->Bind();
	m_Count = count;
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	hasIndices = true;
}

void IndexBuffer::Bind()
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind()
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

bool IndexBuffer::IsInUse()
{
	return hasIndices;
}
