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
	for (size_t i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		
		GL_CALL(glVertexAttribPointer(i,element.count,element.type,element.normalized,vbl.GetStride(),(const void*)offset));
		GL_CALL(glEnableVertexAttribArray(i));
		offset += element.count * GL_SIZEOF(element.type);
	}
}

void VertexArray::Bind()
{
	GL_CALL(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind()
{
	GL_CALL(glBindVertexArray(0));
}

