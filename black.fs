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
out vec4 fragmentColor;

void main()
{
    vec4 colorA = texture(shaderTextureA, shaderTexCoord);
    vec4 colorB = texture(shaderTextureB, shaderTexCoord + time * 0.2 + shaderTexCoord.y);
    fragmentColor = mix(colorA, colorB, sin(time)+1.0);
}