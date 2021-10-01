#pragma once
#include "GL_CALL.h"
#include "RenderTarget.h"
#include "KManager.h"
#include "Color.h"




class CubeVoxel : public RenderTarget {

private:
	int m_ID = -1;
	glm::mat4 m_ModelMatrix;
	char m_ScaleX=1, m_ScaleY=1, m_ScaleZ=1;
	Vector3i m_CurrentPosition;
	Color m_Color;
	bool m_IsRendered = false;

	void SetupModelMatrix();
	void Reset();
	friend class KManager;
protected:
	void SetupForDrawing(unsigned int m_ID);


	const glm::mat4& GetModelMatrix() { return m_ModelMatrix; }
	friend class RenderWindow;

public:
	CubeVoxel();
	~CubeVoxel();

	KDrawData GetDrawData(unsigned int id);
	void Move(int x,int y,int z);
	void SetPosition(int x, int y, int z);
	void SetColor(Color color);
	void SetScale(char x, char y, char z) { m_ScaleX = x; m_ScaleY = y; m_ScaleZ = z; };
	const Vector3i& GetPosition();
	Vector3f GetPositionInWorldSpace();
	const Vector3f& GetColor() { return m_Color.getNormalized(); };
	
};