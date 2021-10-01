#pragma once
#include "GL_CALL.h"



class ShaderStorageBuffer {

private:
	unsigned int m_ID;

public:
	ShaderStorageBuffer();
	virtual ~ShaderStorageBuffer();


	void CreateBuffer(void* data,int dataSize, GLenum access = GL_DYNAMIC_COPY);
	GLvoid* MapBufferPointer();
	void UnMapBufferPointer();

	void SetBinding(int binding=0);
	void Bind();
	void Unbind();

};
