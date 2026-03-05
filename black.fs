/******************************************************************************
 * This is a fragment shader that simply takes a color input (coming from the
 * vertex shader) and makes it the final color of the fragment.
 *
 * Note that the color coming from the vertex shader is an interpolated value
 * coming from three vertices that make up a given triangle, which explains
 * why a gradient is created in the final image.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

in vec3 shaderColor;
in vec2 shaderTexCoord;
uniform float time;
uniform sampler2D shaderTextureA;
uniform sampler2D shaderTextureB;
uniform sampler2D shaderTextureC;
out vec4 fragmentColor;

void main()
{
    vec4 colorA = texture(shaderTextureA, shaderTexCoord);
    vec4 colorB = texture(shaderTextureB, shaderTexCoord + time * 0.2 + shaderTexCoord.y);
    vec4 colorC = texture(shaderTextureC, shaderTexCoord * -tan(time));
    vec4 colormix = mix(colorB, colorC, 0.5f);
    fragmentColor = vec4(shaderColor, 1.0) * mix(colorA, colormix, time);
}