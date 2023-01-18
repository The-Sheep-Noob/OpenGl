#version 330 core

/*layout(location = 0)*/ in vec4 pos;

vec4 test = pos;
uniform float add;

void main() {
    test.x += add;
    gl_Position = test;
}