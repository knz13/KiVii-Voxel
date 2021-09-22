#include "CubeVoxel.h"
#include "RenderWindow.h"


void CubeVoxel::SetupModelMatrix()
{
	m_ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_CurrentPosition.x, m_CurrentPosition.y, m_CurrentPosition.z));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_CurrentRotation.x), glm::vec3(1, 0, 0));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_CurrentRotation.y), glm::vec3(0, 1, 0));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_CurrentRotation.z), glm::vec3(0, 0, 1));
	m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(currentScale, currentScale, currentScale));
}

void CubeVoxel::SetupForDrawing(unsigned int m_ID)
{
	this->SetupModelMatrix();

	this->GetShader().SetUniform3f("instances[" + to_string(m_ID) + "].color", m_Color.getNormalized().x, m_Color.getNormalized().y, m_Color.getNormalized().z);
	this->GetShader().SetUniformMat4f("u_View", KManager::GetWindow()->GetView());
	this->GetShader().SetUniformMat4f("u_Projection", KManager::GetWindow()->GetProjection());

}

void CubeVoxel::Reset()
{
	m_ModelMatrix = glm::mat4(1.0f);
	m_CurrentPosition = { 0,0,0 };
	m_CurrentRotation = { 0,0,0 };
	m_Color = Color::White;
	currentScale = 1.0f;
}

CubeVoxel::CubeVoxel()
	:m_ModelMatrix(glm::mat4(1.0f)), m_CurrentPosition({ 0,0,0 }), m_CurrentRotation({ 0,0,0 }), m_Color(Color::White), currentScale(1.0f)
{
	KManager::AddCube(this);
}

CubeVoxel::~CubeVoxel()
{
}

void CubeVoxel::Move(float x, float y, float z)
{
	m_CurrentPosition.x += x;
	m_CurrentPosition.y += y;
	m_CurrentPosition.z += z;
}

void CubeVoxel::Rotate(float x, float y, float z)
{

	m_CurrentRotation.x += x;
	m_CurrentRotation.y += y;
	m_CurrentRotation.z += z;

}

void CubeVoxel::SetPosition(float x, float y, float z)
{

	m_CurrentPosition.x = x;
	m_CurrentPosition.y = y;
	m_CurrentPosition.z = z;


}

void CubeVoxel::SetRotation(float x, float y, float z)
{
	m_CurrentRotation.x = x;
	m_CurrentRotation.y = y;
	m_CurrentRotation.z = z;
}

void CubeVoxel::SetColor(Color color)
{
	m_Color = color;
}

const Vector3f& CubeVoxel::GetPosition()
{
	return m_CurrentRotation;
}

const Vector3f& CubeVoxel::GetRotation()
{
	return m_CurrentRotation;
}

void CubeVoxel::SetScale(float scale)
{
	currentScale = scale;
}
