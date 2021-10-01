#include "ComputeShader.h"

ComputeShader::ComputeShader()
	:maxWorkGroups({0,0,0})
{
}

ComputeShader::~ComputeShader()
{
}

void ComputeShader::Dispatch(int x_work_groups, int y_work_groups, int z_work_groups)
{
	this->Bind();
	GL_CALL(glDispatchCompute(x_work_groups, y_work_groups, z_work_groups));
}

void ComputeShader::Join()
{
	GL_CALL(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT));
	this->Unbind();
}

void ComputeShader::Init()
{
	GL_CALL(glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &maxWorkGroups.x));
	GL_CALL(glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &maxWorkGroups.y));
	GL_CALL(glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &maxWorkGroups.z));

	cout << "Max Work Groups: ";
	printVec3(maxWorkGroups);
}
