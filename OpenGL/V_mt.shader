#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec3 color;

out vec4 rgb_color;
uniform mat4 cam;

void main() {
    gl_Position = cam * pos;
    rgb_color = vec4(color, 1.0f);
}