#version 430 core


layout(location=0) in vec2 position;


out vec2 UV;

void main() {
	
	gl_Position= vec4(position,0,1.0f);
	UV = position;

}