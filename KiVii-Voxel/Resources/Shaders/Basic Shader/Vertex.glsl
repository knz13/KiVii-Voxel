#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in mat4 instanceMatrix;



uniform mat4 u_Projection;
uniform mat4 u_View;

out vec3 InstanceColor;
flat out int InstanceID;

void main()
{

    InstanceColor = aColor;
    InstanceID = gl_InstanceID;
    gl_Position = u_Projection * u_View * instanceMatrix * vec4(aPos, 1.0f);
}