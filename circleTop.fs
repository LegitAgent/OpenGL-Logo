#version 330 core

in vec3 worldSpacePosition;
in vec3 worldSpaceNormal;
in vec3 objectColor;
in vec2 shaderUV;

uniform sampler2D top_texture;
uniform vec3 cameraPos;

out vec4 fragmentColor;

void main() {
  vec3 lightPosition = vec3(2.0, 2.0, 0.0);
  vec3 l = normalize(vec3(1.0, 1.0, 0.5));
  vec3 n = normalize(worldSpaceNormal);
  float diffuseColor = max(dot(n, l), 0.0);
  float ambientColor = 0.3f;

  vec3 viewDir = normalize(cameraPos - worldSpacePosition);
  vec3 reflectDir = reflect(-l, n);
  float shine = 64.0;
  float specularLight = pow(max(dot(viewDir, reflectDir), 0.0), shine);
  float specularStrength = 0.6;
  vec4 texColor = texture(top_texture, shaderUV);
  float lighting = ambientColor + diffuseColor + specularStrength * specularLight;
  fragmentColor = texColor * vec4(lighting * objectColor, 1.0f);
}