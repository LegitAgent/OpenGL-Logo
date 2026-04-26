#version 330 core

in vec3 worldSpacePosition;
in vec3 worldSpaceNormal;
in vec3 objectColor;
in vec2 shaderUV;

uniform sampler2D top_texture;

out vec4 fragmentColor;

void main() {
  vec3 lightPosition = vec3(2.0, 2.0, 0.0);
  vec3 l = normalize(lightPosition - worldSpacePosition);
  vec3 n = normalize(worldSpaceNormal);
  float diffuseColor = max(dot(n, l), 0.0);
  float ambientColor = 0.3f;
  vec4 texColor = texture(top_texture, shaderUV);
  fragmentColor = texColor * vec4((diffuseColor + ambientColor) * objectColor, 1.0f);
}