#pragma once
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "GL_CALL.h"
#include "KManager.h"
#include "IndexBuffer.h"

class RenderWindow;
class RenderTarget {

private:
	static RenderWindow* win;
	static Shader m_Shader;
	static VertexBuffer m_VBO;
	static VertexArray m_VAO;
	static VertexBufferLayout m_VBL;
	static IndexBuffer m_IB;

	friend class KManager;
protected:
	static RenderWindow* GetWindowPointer() { return win; }
	
	
	static VertexBuffer& GetVertexBuffer() { return RenderTarget::m_VBO; }
	static VertexBufferLayout& GetLayout() { return RenderTarget::m_VBL; }
	static VertexArray& GetVertexArray() { return RenderTarget::m_VAO; }
	static IndexBuffer& GetIndexBuffer() { return RenderTarget::m_IB; }
	static Shader& GetShader() { return m_Shader; }

	static unsigned int GetVertexBufferID() { return m_VBO.m_RendererID; }


	void SetupVertexArray();
	

	static void BindBuffers();
	static void Init();

	friend class KManager;
	friend class RenderWindow;
public:
	RenderTarget();
	~RenderTarget();


	
	

};
