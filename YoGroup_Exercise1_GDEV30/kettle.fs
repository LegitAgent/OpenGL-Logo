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
in vec2 uv;
out vec4 fragmentColor;

void main()
{
    vec3 color1 = vec3(0.5f, 0.3f, 0.0f);
    vec3 color2 = vec3(0.8f, 0.6f, 0.0f);
    float t = 2.0 * uv.y;
    vec3 mixedColors = color1 * (1.0 - t) + color2 * t;
    fragmentColor = vec4(mixedColors, 1.0f);
}
