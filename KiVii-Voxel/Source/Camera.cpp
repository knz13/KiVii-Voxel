#include "Camera.h"
#include "RenderWindow.h"
#include "KManager.h"

void Camera::CalculateFrustrumPlanes()
{
	Vector4f nearNormal, farNormal, leftNormal, rightNormal, topNormal, bottomNormal;
	glm::mat4 projMat = glm::perspective(glm::radians(this->m_Fov+m_Frustrum.frustrumFovIncrease), (float)win->GetSize().x / win->GetSize().y, win->GetRenderNearCutOff(), win->GetRenderDistance());
	glm::mat4 viewProjMat0 = projMat * this->GetView();
	m_Frustrum.inverseViewProjMat = glm::inverse(viewProjMat0);

	float viewProjMat[] = {
		viewProjMat0[0][0],viewProjMat0[0][1],viewProjMat0[0][2],viewProjMat0[0][3],
		viewProjMat0[1][0],viewProjMat0[1][1],viewProjMat0[1][2],viewProjMat0[1][3],
		viewProjMat0[2][0],viewProjMat0[2][1],viewProjMat0[2][2],viewProjMat0[2][3],
		viewProjMat0[3][0],viewProjMat0[3][1],viewProjMat0[3][2],viewProjMat0[3][3],

	};

	/* Extract the numbers for the RIGHT plane */
	rightNormal.x = viewProjMat[3] - viewProjMat[0];
	rightNormal.y = viewProjMat[7] - viewProjMat[4];
	rightNormal.z = viewProjMat[11] - viewProjMat[8];
	rightNormal.w = viewProjMat[15] - viewProjMat[12];
	/* Normalize the result */
	float t = sqrt(pow(rightNormal.x, 2) + pow(rightNormal.y, 2) + pow(rightNormal.z, 2));
	rightNormal.x /= t;
	rightNormal.y /= t;
	rightNormal.z /= t;
	rightNormal.w /= t;
	/* Extract the numbers for the LEFT plane */
	leftNormal.x = viewProjMat[3] + viewProjMat[0];
	leftNormal.y = viewProjMat[7] + viewProjMat[4];
	leftNormal.z = viewProjMat[11] + viewProjMat[8];
	leftNormal.w = viewProjMat[15] + viewProjMat[12];
	/* Normalize the result */
	t = sqrt(pow(leftNormal.x, 2) + pow(leftNormal.y, 2) + pow(leftNormal.z, 2));
	leftNormal.x /= t;
	leftNormal.y /= t;
	leftNormal.z /= t;
	leftNormal.w /= t;
	/* Extract the BOTTOM plane */
	bottomNormal.x = viewProjMat[3] + viewProjMat[1];
	bottomNormal.y = viewProjMat[7] + viewProjMat[5];
	bottomNormal.z = viewProjMat[11] + viewProjMat[9];
	bottomNormal.w = viewProjMat[15] + viewProjMat[13];
	/* Normalize the result */
	t = sqrt(pow(bottomNormal.x, 2) + pow(bottomNormal.y, 2) + pow(bottomNormal.z, 2));
	bottomNormal.x /= t;
	bottomNormal.y /= t;
	bottomNormal.z /= t;
	bottomNormal.w /= t;
	/* Extract the TOP plane */
	topNormal.x = viewProjMat[3] - viewProjMat[1];
	topNormal.y = viewProjMat[7] - viewProjMat[5];
	topNormal.z = viewProjMat[11] - viewProjMat[9];
	topNormal.w = viewProjMat[15] - viewProjMat[13];
	/* Normalize the result */
	t = sqrt(pow(topNormal.x, 2) + pow(topNormal.y, 2) + pow(topNormal.z, 2));
	topNormal.x /= t;
	topNormal.y /= t;
	topNormal.z /= t;
	topNormal.w /= t;
	/* Extract the FAR plane */
	farNormal.x = viewProjMat[3] - viewProjMat[2];
	farNormal.y = viewProjMat[7] - viewProjMat[6];
	farNormal.z = viewProjMat[11] - viewProjMat[10];
	farNormal.w = viewProjMat[15] - viewProjMat[14];
	/* Normalize the result */
	t = sqrt(pow(farNormal.x, 2) + pow(farNormal.y, 2) + pow(farNormal.z, 2));
	farNormal.x /= t;
	farNormal.y /= t;
	farNormal.z /= t;
	farNormal.w /= t;
	/* Extract the NEAR plane */
	nearNormal.x = viewProjMat[3] + viewProjMat[2];
	nearNormal.y = viewProjMat[7] + viewProjMat[6];
	nearNormal.z = viewProjMat[11] + viewProjMat[10];
	nearNormal.w = viewProjMat[15] + viewProjMat[14];
	/* Normalize the result */
	t = sqrt(pow(nearNormal.x, 2) + pow(nearNormal.y, 2) + pow(nearNormal.z, 2));
	nearNormal.x /= t;
	nearNormal.y /= t;
	nearNormal.z /= t;
	nearNormal.w /= t;
	

	m_Frustrum.planeNormals = { nearNormal,farNormal,leftNormal,rightNormal,topNormal,bottomNormal };
}

void Camera::Update()
{
	if (canMove) {
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

			this->RotateCamera(((int)(newX)-(int)(KManager::GetWindow()->GetSize().x / 2)) * m_Sensitivity, ((int)(KManager::GetWindow()->GetSize().y / 2) - (int)newY) * m_Sensitivity);

		}


		if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_W) == GLFW_PRESS) {
			this->Move(m_Front.x * m_MovingSpeed, 0, m_Front.z * m_MovingSpeed);
		}
		if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_S) == GLFW_PRESS) {
			this->Move(-m_Front.x * m_MovingSpeed, 0, -m_Front.z * m_MovingSpeed);
		}
		if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_A) == GLFW_PRESS) {
			this->Move(-m_Right.x * m_MovingSpeed, 0, -m_Right.z * m_MovingSpeed);
		}
		if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_D) == GLFW_PRESS) {
			this->Move(m_Right.x * m_MovingSpeed, 0, m_Right.z * m_MovingSpeed);
		}
		if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			this->Move(0, -m_MovingSpeed, 0);
		}
		if (glfwGetKey(KManager::GetGLFWwindowPointer(), GLFW_KEY_SPACE) == GLFW_PRESS) {
			this->Move(0, m_MovingSpeed, 0);
		}
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

	this->CalculateFrustrumPlanes();
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
	/*
	cout << "Near Normal = ";
	printVec3(m_Frustrum.planeNormals[0]);
	cout << "Far Normal = ";
	printVec3(m_Frustrum.planeNormals[1]);
	cout << "Left Normal = ";
	printVec3(m_Frustrum.planeNormals[2]);
	cout << "Right Normal = ";
	printVec3(m_Frustrum.planeNormals[3]);

	cout << endl;
	*/
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

bool Camera::IsPointInFrustrum(Vector3f point)
{
	for (auto& plane : m_Frustrum.planeNormals) {
		if (plane.x * point.x + plane.y * point.y + plane.z * point.z + plane.w <= 0) {
			return false;
		}
	}
	return true;
}

bool Camera::IsVoxelInFrustrum(Vector3i voxelPos, float voxelHalfSize)
{
	Vector3f voxelPosInWorldSpace = KManager::GetVoxelPosInWorldSpace(voxelPos);
	for (auto& plane : m_Frustrum.planeNormals) {
		if (plane.x * voxelPosInWorldSpace.x + plane.y * voxelPosInWorldSpace.y + plane.z * voxelPosInWorldSpace.z + plane.w <= -(float)(voxelHalfSize*sqrt(3)/2.0f)) {
			return false;
		}
	}
	return true;
}






