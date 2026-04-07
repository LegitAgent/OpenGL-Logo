#version 330 core

in vec3 shaderColor;
in vec2 shaderUV;

uniform sampler2D top_texture;

out vec4 fragmentColor;

void main() {
vec4 texColor = texture(top_texture, shaderUV);
fragmentColor = texColor * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}