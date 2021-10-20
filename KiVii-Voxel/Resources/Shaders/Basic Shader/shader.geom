#version 430 core

layout (points) in;
layout (triangle_strip,max_vertices=3) out;

in VS_OUT
{
	vec3 color;
	mat4 viewProjMat;
	float voxelSize;
	
} vs_out[];



//uniform float voxelSize;
//uniform mat4 u_ProjectionViewMat;



int indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
};

out vec3 InstanceColor;


void main() 
{
	float voxelSize = vs_out[gl_PrimitiveIDIn].voxelSize;

	vec4 vertices[] = {
	vec4(-voxelSize/2,-voxelSize/2.0f,-voxelSize/2.0f,0),
	vec4(voxelSize/2,-voxelSize/2.0f,-voxelSize/2.0f,0),
	vec4(voxelSize/2,voxelSize/2.0f,-voxelSize/2.0f,0),
	vec4(-voxelSize/2,voxelSize/2.0f,-voxelSize/2.0f,0),
	
	vec4(-voxelSize/2,-voxelSize/2.0f,voxelSize/2.0f,0),
	vec4(voxelSize/2,-voxelSize/2.0f,voxelSize/2.0f,0),
	vec4(voxelSize/2,voxelSize/2.0f,voxelSize/2.0f,0),
	vec4(-voxelSize/2,voxelSize/2.0f,voxelSize/2.0f,0),
	};
	

	InstanceColor = vs_out[0].color;
	for (int i = 0;i<36;i+=3){
		gl_Position = vs_out[0].viewProjMat*(gl_in[0].gl_Position + vertices[i]);
		EmitVertex();
		gl_Position = vs_out[0].viewProjMat*(gl_in[0].gl_Position + vertices[i+1]);
		EmitVertex();
		gl_Position = vs_out[0].viewProjMat*(gl_in[0].gl_Position + vertices[i+2]);
		EmitVertex();
		
		EndPrimitive();

	}
	



}