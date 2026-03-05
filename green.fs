#version 330 core

in vec3 shaderColor;
in vec2 mainTexCoord;
in vec2 troyTexCoord;
uniform sampler2D mainTexture;
uniform sampler2D troyTexture;
uniform float time;
uniform float speed;
out vec4 fragmentColor;

void main()
{
    vec4 colorA = texture(mainTexture, mainTexCoord);
    colorA *= vec4(shaderColor, 1.0);
    vec4 colorB = texture(troyTexture, troyTexCoord + time);
    fragmentColor = mix(colorA, colorB, time);
}