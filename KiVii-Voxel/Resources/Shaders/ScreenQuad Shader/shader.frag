#version 430 core



in vec2 UV;

uniform sampler2D tex0;

out vec4 FragColor;

void main() {
	
	vec2 transformedCoords = vec2((UV.x+1)/2.0f,(UV.y+1)/2.0f);
	FragColor = texture(tex0,transformedCoords);

}