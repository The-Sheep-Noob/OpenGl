#version 330 core

out vec4 color;
uniform float colorf;

void main() {
	color = vec4(colorf , 0.5 / colorf, 0.5f, 1.0f);
}