#pragma once
#include "glm/glm.hpp"
#include "GL_CALL.h"




class RenderWindow;
class Camera {
	struct Frustrum {
		vector<Vector3f> planeNormals;
	};
private:
	int m_ID = -1;
	RenderWindow* win;
	glm::mat4 m_CurrentView;
	glm::vec3 m_LookingAt;
	glm::vec3 m_CurrentPos;
	glm::vec3 m_Direction;
	glm::vec3 m_Right;
	glm::vec3 m_Up;
	glm::vec3 m_Front;
	float m_MovingSpeed;
	float m_Sensitivity;
	float pitch, yaw;
	float m_Fov;
	bool canMove = true;
	Frustrum m_Frustrum;

	void CalculateFrustrumPlaneNormals();

	friend class KManager;
protected:
	void Update();

	friend class RenderWindow;
public:
	Camera();
	~Camera();

	void Bind();
	
	void LookTo(float x, float y, float z);
	void RotateCamera(float x, float y);
	void SetRotation(float x, float y);
	
	void Move(float x, float y, float z);

	void SetMovingSpeed(float speed);
	void SetSensitivity(float sensitivity);
	void SetPosition(float x, float y, float z);
	void SetPosition(glm::vec3 pos);
	void SetStatic(bool b) { canMove = b; };
	void SetFov(float angle) { m_Fov = angle; };

	float GetFov() { return m_Fov; }
	glm::vec3 GetDirectionVector() { return m_Front; }
	glm::vec3 GetUpVector() { return m_Up; }
	glm::mat4 GetView() {  return m_CurrentView; }
	bool CheckIfPointInFrustrum(Vector3f point);
	glm::vec3 GetPosition() { return m_CurrentPos; }
};