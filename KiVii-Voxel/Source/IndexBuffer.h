#pragma once
#include "GL_CALL.h"


class IndexBuffer {
private:
	unsigned int m_RendererID;
	bool hasIndices = false;
	unsigned int m_Count;

	void Init();

	friend class KManager;
public:
	IndexBuffer();
	~IndexBuffer();

	void CreateBuffer(void* data, unsigned int count);

	void Bind();
	void Unbind();
	bool IsInUse();

	unsigned int GetCount() { return m_Count; }
};


