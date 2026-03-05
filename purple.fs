#version 330 core

in vec3 shaderColor;
in vec2 shaderTexCoord;
in vec2 textureDisplacement;
uniform float time;
uniform sampler2D shaderTextureA;
uniform sampler2D shaderTextureB;
out vec4 fragmentColor;

void main()
{
    float newTime = time;
    newTime *= 2;
    vec4 colorA = texture(shaderTextureA, shaderTexCoord);
    vec2 texDisp = textureDisplacement;
    texDisp.y += -sin(texDisp.x * 1.2 + newTime * 1.5) * 0.5;
    texDisp.x *= (1/colorA.r) * 0.2;
    vec4 colorB = texture(shaderTextureB, texDisp);
    fragmentColor = vec4(shaderColor, 1.0) *
        mix(colorA, colorB, newTime);
}