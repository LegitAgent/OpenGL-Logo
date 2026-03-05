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
    vec2 newTexCoord = shaderTexCoord;
    newTexCoord.x = newTexCoord.x * cos(time) - newTexCoord.y * sin(time);
    newTexCoord.y = newTexCoord.x * sin(time) + newTexCoord.y * cos(time);
    vec4 colorB = texture(shaderTextureB, newTexCoord);
    fragmentColor = vec4(shaderColor, 1.0) *
        mix(colorA, colorB, time);
}