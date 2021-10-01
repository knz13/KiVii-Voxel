#include "ShaderStorageBuffer.h"

ShaderStorageBuffer::ShaderStorageBuffer()
{
	GL_CALL(glGenBuffers(1, &m_ID));
	
}

ShaderStorageBuffer::~ShaderStorageBuffer()
{
}

void ShaderStorageBuffer::CreateBuffer(void* data,int dataSize, GLenum access)
{
	this->Bind();
	GL_CALL(glBufferData(GL_SHADER_STORAGE_BUFFER, dataSize, data, access));
	this->Unbind();
}

GLvoid* ShaderStorageBuffer::MapBufferPointer()
{
	this->Bind();
	GLvoid* ptr;
	GL_CALL_WITH_RETURN(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY),ptr);
	return ptr;
}

void ShaderStorageBuffer::UnMapBufferPointer()
{
	GL_CALL(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER));
	this->Unbind();
}

void ShaderStorageBuffer::SetBinding(int binding)
{
	GL_CALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, m_ID));
}

void ShaderStorageBuffer::Bind()
{
	GL_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ID));
	
}

void ShaderStorageBuffer::Unbind()
{
	GL_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
}
