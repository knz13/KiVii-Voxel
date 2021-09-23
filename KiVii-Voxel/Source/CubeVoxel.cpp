#include "CubeVoxel.h"
#include "RenderWindow.h"


void CubeVoxel::SetupModelMatrix()
{
	m_ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_CurrentPosition.x, m_CurrentPosition.y, m_CurrentPosition.z));
}

void CubeVoxel::SetupForDrawing(unsigned int m_ID)
{
	this->GetShader().Bind();
	this->SetupModelMatrix();

	//this->GetShader().SetUniform3f("instances[" + to_string(m_ID) + "].color", m_Color.getNormalized().x, m_Color.getNormalized().y, m_Color.getNormalized().z);
	this->GetShader().SetUniformMat4f("u_View", KManager::GetWindow()->GetView());
	this->GetShader().SetUniformMat4f("u_Projection", KManager::GetWindow()->GetProjection());

}

void CubeVoxel::Reset()
{
	m_ModelMatrix = glm::mat4(1.0f);
	m_CurrentPosition = { 0,0,0 };
	m_Color = Color::White;
	
}

CubeVoxel::CubeVoxel()
	:m_ModelMatrix(glm::mat4(1.0f)), m_CurrentPosition({ 0,0,0 }), m_Color(Color::White)
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

void CubeVoxel::SetPosition(float x, float y, float z)
{

	m_CurrentPosition.x = x;
	m_CurrentPosition.y = y;
	m_CurrentPosition.z = z;


}

void CubeVoxel::SetColor(Color color)
{
	m_Color = color;
}

const Vector3f& CubeVoxel::GetPosition()
{
	return m_CurrentPosition;
}




