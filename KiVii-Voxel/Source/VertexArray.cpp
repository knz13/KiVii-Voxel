#include "VertexArray.h"

void VertexArray::Init()
{
	GL_CALL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::VertexArray()
{
	

}

void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout vbl)
{
	this->Bind();
	vb.Bind();
	unsigned int offset = 0;
	const auto& elements = vbl.GetElements();
	for (size_t i = (size_t)m_indexOffset; i < elements.size()+(size_t)m_indexOffset; i++) {
		const auto& element = elements[i-m_indexOffset];
		
		GL_CALL(glEnableVertexAttribArray(i));
		GL_CALL(glVertexAttribPointer(i,element.count,element.type,element.normalized,vbl.GetStride(),(const void*)(offset)));
		if (element.hasDivisor) {
			GL_CALL(glVertexAttribDivisor(i, 1));
		}
		offset += element.count * GL_SIZEOF(element.type);
		
	}
	m_cummulativeOffset += offset;
	m_indexOffset += (unsigned int)elements.size();
	
}

void VertexArray::Bind()
{
	GL_CALL(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind()
{
	GL_CALL(glBindVertexArray(0));
}

