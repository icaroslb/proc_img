#version 430 core

in vec2 coord;

uniform sampler2D Textura;

out vec4 FragColor;

void main () {
	FragColor = texture(Textura, coord);
}