#pragma once
#include "GL_CALL.h"
#include "Shader.h"


class ComputeShader : public Shader {

	Vector3i maxWorkGroups;


public:
	ComputeShader();
	virtual ~ComputeShader();


	void Dispatch(int x_work_groups, int y_work_groups, int z_work_groups);
	void Join(GLenum barrier = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	void Init();

};

