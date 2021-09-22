#version 400 core


out vec4 FragColor;

struct InstanceData {
    vec3 color;
};

const int MAX_NUM_OBJECTS = 10000;

uniform InstanceData instances[MAX_NUM_OBJECTS];

in vec3 FragPos;




void main()
{
    
    FragColor = vec4(instances[gl_instanceID].color, 1.0f);
    
   
}