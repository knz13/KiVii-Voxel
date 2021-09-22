#pragma once
#include "GL_CALL.h"
#include "RenderTarget.h"
#include "KManager.h"
#include "Color.h"


class CubeVoxel : public RenderTarget {

private:
	int m_ID = -1;
	glm::mat4 m_ModelMatrix;
	Vector3f m_CurrentPosition;
	Vector3f m_CurrentRotation;
	Color m_Color;
	float currentScale;

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


	void Move(float x,float y,float z);
	void Rotate(float x, float y, float z);

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float scale);
	void SetColor(Color color);

	const Vector3f& GetPosition();
	const Vector3f& GetRotation();

	
};