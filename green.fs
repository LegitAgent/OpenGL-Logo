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
in vec2 troyTexCoord;
uniform sampler2D mainTexture;
uniform sampler2D troyTexture;
uniform float time;
uniform float speed;
out vec4 fragmentColor;

void main()
{
    vec4 colorA = texture(mainTexture, mainTexCoord);
    vec2 troyTexCoordReal = troyTexCoord;
    troyTexCoordReal.x += time;
    troyTexCoordReal.y -= time;
    vec4 colorB = texture(troyTexture, troyTexCoordReal);
    fragmentColor = vec4(shaderColor, 1.0f) * 
        mix(colorA, colorB, sin(time)+1.0);
}