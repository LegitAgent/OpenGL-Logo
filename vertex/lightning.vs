/******************************************************************************
 * This is a vertex shader that assumes that each vertex has a position and
 * color. The color of the vertex is further manipulated via a uniform, and
 * this color is passed to the fragment shader as an output.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#version 330 core

uniform float time;
uniform float speed;

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

out vec3 shaderColor;
out vec2 uv;

void main()
{
    float amplitude = 0.1;
    float height = 0.2;

    float angle = time * speed;

    float offsetX = sin(angle) * amplitude;
    float offsetY = abs(cos(angle)) * height; // makes it bounce up

    vec3 newPos = vertexPosition;
    newPos.x += offsetX;
    newPos.y += offsetY;

    gl_Position = vec4(newPos, 1.0);
    gl_Position.y += 0.4f;
    uv.x = gl_Position.x;
    uv.y = gl_Position.y;
    shaderColor = vertexColor;
}
