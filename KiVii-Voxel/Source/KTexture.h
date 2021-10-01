#pragma once
#include "GL_CALL.h"



class KTexture {
private:
	unsigned int m_ID;
	GLenum m_Type;
	bool isInit = false;
public:

	KTexture();
	virtual ~KTexture();

	void Init(GLenum type, int width, int height, void* data = nullptr, int internalFormat = GL_RGB, int border = 0, GLenum format = GL_RGB);
	void BindImageTexture(int position,GLenum access,GLenum format);
	void Bind(int position);
	void Unbind();
};

