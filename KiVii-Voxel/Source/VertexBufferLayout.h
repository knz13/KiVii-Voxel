#pragma once
#include "GL_CALL.h"
#include <vector>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	bool hasDivisor = false;
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
	unsigned int m_Count;

public:
	VertexBufferLayout() 
		:m_Stride(0),m_Count(0)
	{};
	~VertexBufferLayout() {};

	template<typename T>
	void Push(unsigned int count, bool hasDivisor = false) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count, bool hasDivisor) {
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += GL_SIZEOF(GL_FLOAT) * count;
		m_Count++;
	}

	template<>
	void Push<unsigned int>(unsigned int count, bool hasDivisor) {
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_TRUE });
		m_Stride += GL_SIZEOF(GL_UNSIGNED_INT) * count;
		m_Count++;
	}
	template<>
	void Push<unsigned char>(unsigned int count, bool hasDivisor) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += GL_SIZEOF(GL_UNSIGNED_BYTE) * count;
		m_Count++;
	}
	template<>
	void Push<glm::mat4>(unsigned int count, bool hasDivisor) {
		for (int i = 0; i < 4*(int)count; i++) {
			m_Elements.push_back({ GL_FLOAT, 4, GL_FALSE,hasDivisor});
			m_Stride += GL_SIZEOF(GL_FLOAT) * 4;
			m_Count++;
		}
		
	}

	
	void Reset() { m_Elements.clear(); m_Stride = 0; m_Count = 0; }
	inline const vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
	inline unsigned int GetCount() const { return m_Count; }

};