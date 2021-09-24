#pragma once
#include "GL_CALL.h"
#include "RenderTarget.h"
#include "KManager.h"
#include "Color.h"


class CubeVoxel : public RenderTarget {

private:
	int m_ID = -1;
	glm::mat4 m_ModelMatrix;
	Vector3i m_CurrentPosition;
	Color m_Color;

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


	void Move(int x,int y,int z);
	void SetPosition(int x, int y, int z);
	void SetColor(Color color);
	const Vector3i& GetPosition();
	Vector3f GetPositionInWorldSpace();
	Vector3f GetColor() { return m_Color.getNormalized(); };
	
};