#version 330 core


out vec4 FragColor;

struct InstanceData {
    vec3 color;
};

const int MAX_NUM_OBJECTS = 1000;

uniform InstanceData instances[MAX_NUM_OBJECTS];

in vec3 FragPos;
in vec3 InstanceColor;

flat in int InstanceID;


void main()
{
    
    FragColor = vec4(InstanceColor, 1.0f);
    
   
}