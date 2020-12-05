#version 330

in vec2 v_texCoord;
out vec4 texColor;

uniform sampler2D tex;

void main() {
    texColor = texture(tex, v_texCoord);
}
