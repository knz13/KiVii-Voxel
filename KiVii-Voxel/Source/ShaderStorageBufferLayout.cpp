#include "ShaderStorageBufferLayout.h"

ShaderStorageBufferLayout::ShaderStorageBufferLayout()
	:m_HasChanged(false)
{
	m_Elements.reserve(10);
	for (unsigned long int i = 0; i < 10; i++) {
		m_FreeIndices.push(i);
	}
}

ShaderStorageBufferLayout::~ShaderStorageBufferLayout()
{

}

bool ShaderStorageBufferLayout::RemoveFromLayout(unsigned long int index)
{
	if (m_Elements.at(index).available) {
		m_Elements.at(index).available = false;
		m_FreeIndices.push(index);
		return true;
	}
	else {
		return false;
	}
}

unsigned long int ShaderStorageBufferLayout::GetFreeIndex()
{
	if (m_FreeIndices.size() > 0) {
		unsigned long int i = m_FreeIndices.front();
		m_FreeIndices.pop();
		return i;
	}
	else {
		m_Elements.push_back({ {},0,false });
		m_FreeIndices.push(m_Elements.size() - 1);
		unsigned long int i = m_FreeIndices.front();
		m_FreeIndices.pop();
		return i;
		
	}
}
