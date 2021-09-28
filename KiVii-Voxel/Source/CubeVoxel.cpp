#include "CubeVoxel.h"
#include "RenderWindow.h"



void CubeVoxel::SetupModelMatrix()
{
	m_ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_CurrentPosition.x*VOXEL_ENTITY_SIZE, m_CurrentPosition.y*VOXEL_ENTITY_SIZE, m_CurrentPosition.z*VOXEL_ENTITY_SIZE));
	m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(m_ScaleX, m_ScaleY, m_ScaleZ));
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
	m_CurrentPosition = { 0,-1,0 };
	m_Color = Color::White;
	
}

CubeVoxel::CubeVoxel()
	:m_ModelMatrix(glm::mat4(1.0f)), m_CurrentPosition({ 0,-1,0 }), m_Color(Color::White)
{
	KManager::AddCube(this);
}

CubeVoxel::~CubeVoxel()
{
}

void CubeVoxel::Move(int x, int y, int z)
{


	m_CurrentPosition.x += x;
	if (m_CurrentPosition.y + y >= 0) {
		m_CurrentPosition.y += y;
	}
	
	m_CurrentPosition.z += z;
	
	
}

void CubeVoxel::SetPosition(int x, int y, int z)
{
	

	m_CurrentPosition.x = x;
	if (y >= 0) {
		m_CurrentPosition.y = y;
	}
	m_CurrentPosition.z = z;

	 
	
}

void CubeVoxel::SetColor(Color color)
{
	m_Color = color;
}

const Vector3i& CubeVoxel::GetPosition()
{
	return m_CurrentPosition;
}

Vector3f CubeVoxel::GetPositionInWorldSpace()
{
	return Vector3f(m_CurrentPosition.x*VOXEL_ENTITY_SIZE,m_CurrentPosition.y*VOXEL_ENTITY_SIZE,m_CurrentPosition.z*VOXEL_ENTITY_SIZE);
}




