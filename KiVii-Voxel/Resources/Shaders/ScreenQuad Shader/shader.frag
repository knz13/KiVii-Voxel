#version 430 core



in vec2 UV;

uniform sampler2D tex0;

out vec4 FragColor;

void main() {
	
	FragColor = texture(tex0,UV);

}