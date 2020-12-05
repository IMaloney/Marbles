#version 330 core

layout(location = 0) in vec3 position;
layout(location = 5) in vec2 texCoord;


out vec2 v_texCoord;



void main() {

    gl_Position = vec4(position, 1.0);
    v_texCoord = texCoord;
}
