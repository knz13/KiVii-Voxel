#pragma once
#include "GL_CALL.h"
#include <any>

#define K_FLOAT sizeof(float)
#define K_MAT4 sizeof(glm::mat4)

struct SSBOLayoutElement {
	std::any data;
	int size;
	bool available;
};

class ShaderStorageBufferLayout {
private:
	vector<SSBOLayoutElement> m_Elements;
	queue<unsigned long int> m_FreeIndices;
	bool m_HasChanged;
	unsigned long int m_LayoutSize = 0;

	friend class ShaderStorageBuffer;
	friend class KManager;
public:
	ShaderStorageBufferLayout();
	~ShaderStorageBufferLayout();


	unsigned long int GetFreeIndex();
	bool RemoveFromLayout(unsigned long int index);

	template<typename T>
	void Modify(unsigned long int index,T data,int size);

	

};

template<typename T>
inline void ShaderStorageBufferLayout::Modify(unsigned long int index, T data, int size)
{
	if (m_Elements.at(index).available) {
		m_Elements.at(index).data = data;
		m_Elements.at(index).size = size;
		m_LayoutSize += size;
	}
	else {
		m_LayoutSize -= m_Elements.at(index).size;
		m_Elements.at(index).data = data;
		m_Elements.at(index).size = size;
		m_LayoutSize += size;
	}
}
