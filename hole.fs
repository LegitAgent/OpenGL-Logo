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

uniform float time;
in vec2 uv;
in vec3 shaderColor;
out vec4 fragmentColor;

void main()
{
    vec3 darkSilver = vec3(0.15, 0.15, 0.18);
    vec3 darkViolet = vec3(0.07, 0.0, 0.09);

    float speed = 2.0;
    float interval = 2.0;
    float wave = sin(uv.y * interval + time * speed);

    float t = wave * 0.5 + 0.5;
    
    // exponential average!
    vec3 color = darkSilver * (1.0 - t) + darkViolet * t;

    fragmentColor = vec4(color, 1.0);
}
