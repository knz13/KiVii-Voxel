#version 330 core


out vec4 FragColor;

struct InstanceData {
    vec3 color;
};

const int MAX_NUM_OBJECTS = 1000;

uniform InstanceData instances[MAX_NUM_OBJECTS];
uniform sampler2D tex0;

in vec3 FragPos;
in vec3 InstanceColor;

flat in int InstanceID;


void main()
{
    //FragColor = texture(tex0,ivec2(0.5f,0.5f));
    FragColor = vec4(InstanceColor, 1.0f);
    
   
}