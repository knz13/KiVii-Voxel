#include "KTexture.h"

KTexture::KTexture()
	:m_Type(GL_TEXTURE_2D)
{
}

KTexture::~KTexture()
{
	if (isInit) {
		GL_CALL(glDeleteTextures(1, &m_ID));
	}
}

void KTexture::Init(GLenum type, int width, int height, void* data, int internalFormat, int border, GLenum format)
{
	//todo: add more cases to switch case.
	GL_CALL(glGenTextures(1, &m_ID));
	this->Bind(0);
	GL_CALL(glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_CALL(glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GL_CALL(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	if (data == nullptr) {
		switch (type) {
		case GL_TEXTURE_2D:
			GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL));
			break;
		default:
			GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL));
			break;
		}
	}
	else {
		switch (type) {
		case GL_TEXTURE_2D:
			GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data));
			break;
		default:
			GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data));
			break;
		}
	}
	//GL_CALL(glGenerateMipmap(m_Type));
}

void KTexture::BindImageTexture(int position,GLenum access,GLenum format)
{
	this->Bind(position);
	GL_CALL(glBindImageTexture(position, m_ID, 0, GL_FALSE, 0, access, format));
}

void KTexture::Bind(int position)
{
	
	GL_CALL(glBindTexture(m_Type, m_ID));
	GL_CALL(glActiveTexture(GL_TEXTURE0 + position));
}

void KTexture::Unbind()
{
	GL_CALL(glBindTexture(m_Type, 0));
}
