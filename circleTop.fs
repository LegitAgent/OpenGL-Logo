#version 330 core

in vec3 shaderColor;
in vec2 shaderUV;
in vec3 fragNormal;

uniform sampler2D top_texture;

out vec4 fragmentColor;

void main() {
  vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
  float diff = max(dot(normalize(fragNormal), lightDir), 0.0);
  vec4 texColor = texture(top_texture, shaderUV);
  float ambient = 0.3;
  fragmentColor = texColor * vec4(shaderColor * (ambient + diff), 1.0);
}