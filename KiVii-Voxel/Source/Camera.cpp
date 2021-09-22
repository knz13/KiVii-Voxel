#include "Camera.h"
#include "RenderWindow.h"
#include "KManager.h"

void Camera::Update()
{
	static bool moving = false;

	double newX, newY;
	glfwGetCursorPos(KManager::GetGLFWwindowPointer(), &newX, &newY);

	if (glfwGetMouseButton(KManager::GetGLFWwindowPointer(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && !moving) {
		moving = true;
		glfwSetCursorPos(KManager::GetGLFWwindowPointer(), (double)KManager::GetWindow()->GetSize().x / 2, (double)KManager::GetWindow()->GetSize().y / 2);
		glfwGetCursorPos(KManager::GetGLFWwindowPointer(), &newX, &newY);
		glfwSetInputMode(KManager::GetGLFWwindowPointer(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	if (glfwGetMouseButton(KManager::GetGLFWwindowPointer(), GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
		moving = false;
		glfwSetInputMode(KManager::GetGLFWwindowPointer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (moving) {
		glfwSetCursorPos(KManager::GetGLFWwindowPointer(), (double)KManager::GetWindow()->GetSize().x / 2, (double)KManager::GetWindow()->GetSize().y / 2);

		this->RotateCamera(((int)(newX) - (int)(KManager::GetWindow()->GetSize().x/2))*m_Sensitivity, ((int)(KManager::GetWindow()->GetSize().y / 2) - (int)newY)*m_Sensitivity);
		
	}
	

	if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_W) == GLFW_PRESS) {
		this->Move(m_Front.x*m_MovingSpeed, 0, m_Front.z*m_MovingSpeed);
	}
	if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_S) == GLFW_PRESS) {
		this->Move(-m_Front.x*m_MovingSpeed, 0, -m_Front.z*m_MovingSpeed);
	}
	if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_A) == GLFW_PRESS) {
		this->Move(-m_Right.x*m_MovingSpeed, 0, -m_Right.z*m_MovingSpeed);
	}
	if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_D) == GLFW_PRESS) {
		this->Move(m_Right.x*m_MovingSpeed, 0, m_Right.z*m_MovingSpeed);
	}
	if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		this->Move(0, -m_MovingSpeed, 0);
	}
	if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		this->Move(0, m_MovingSpeed,0);
	}
	
}

Camera::Camera()
	:m_LookingAt({ 0,0,0 }), m_CurrentView(glm::mat4(1.0f)), m_CurrentPos(glm::vec3(0, 0, 0)), m_Direction(glm::vec3(0, 0, 0)), pitch(0.0f), yaw(-90.0f), m_MovingSpeed(8.0f),m_Sensitivity(0.5), m_Fov(45.0f)
{
	m_CurrentView = glm::lookAt(glm::vec3(m_Direction.x, m_Direction.y, m_Direction.z), glm::vec3(m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z), glm::vec3(0.0f, 1.0f, 0.0f));
	
	win = KManager::GetWindow();
	Bind();
	KManager::AddCamera(this);
}

Camera::~Camera()
{

}

void Camera::Bind()
{
	

	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	

	m_Direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_Direction.y = sin(glm::radians(pitch));
	m_Direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	m_Front = glm::normalize(m_Direction);

	m_Right = glm::normalize(glm::cross(m_Front, m_Up));

	m_CurrentView = glm::lookAt(glm::vec3(m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z), glm::vec3(m_CurrentPos.x + m_Direction.x, m_CurrentPos.y + m_Direction.y, m_CurrentPos.z + m_Direction.z), glm::vec3(0.0f, 1.0f, 0.0f));
	//m_CurrentView = glm::lookAt(m_CurrentPos, m_LookingAt, glm::vec3(0,1.0f,0));

}

void Camera::LookTo(float x, float y, float z)
{
	m_LookingAt = glm::vec3(x,y,z);
}

void Camera::RotateCamera(float x, float y)
{
	pitch += y;
	yaw += x;
	
	Bind();
}

void Camera::SetRotation(float x, float y)
{
	pitch = y - 90.0f;
	yaw = x;
	
	Bind();
}

void Camera::Move(float x, float y, float z)
{
	m_CurrentPos += glm::vec3(x * KManager::GetDeltaTime(), y * KManager::GetDeltaTime(), z * KManager::GetDeltaTime());
	Bind();
}

void Camera::SetMovingSpeed(float speed)
{
	m_MovingSpeed = speed;
	Bind();
}

void Camera::SetSensitivity(float sensitivity)
{
	m_Sensitivity = sensitivity;
}

void Camera::SetPosition(float x, float y, float z)
{
	m_CurrentPos = glm::vec3(x, y, z);
	Bind();

}

void Camera::SetPosition(glm::vec3 pos)
{
	m_CurrentPos = pos;
	Bind();
}

