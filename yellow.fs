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
in vec2 mainTexCoord;
in vec2 wolfTexCoord;
uniform sampler2D mainTexture;
uniform sampler2D wolfTexture;
uniform float time;
out vec4 fragmentColor;

void main()
{
    vec4 main = texture(mainTexture, mainTexCoord);
    vec4 wolf = texture(wolfTexture, wolfTexCoord);
    fragmentColor = vec4(shaderColor, 1.0f) * mix(main, wolf, time);
}