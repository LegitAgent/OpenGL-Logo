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
uniform float glow;

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

out vec3 shaderColor;

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

    // Eye-specific vertical bounce
    float eyeBounceAmplitude = 0.05;
    float eyeBounceSpeed = 6.0;

    float eyeOffsetY = sin(time * eyeBounceSpeed) * eyeBounceAmplitude;

    gl_Position = vec4(newPos, 1.0);
    gl_Position.y += 0.23f;
    gl_Position.y += abs(eyeOffsetY);

    shaderColor = vertexColor + glow;
}
