#version 330 core

uniform float time;
uniform float speed;

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexTexCoord;   

out vec3 shaderColor;
out vec2 mainTexCoord;
out vec2 landDispTexCoord;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0);
    gl_Position.x -= 0.5;
    gl_Position.y -= 0.5;

    // Translations
    float x_offset = 0.2;
    gl_Position.x += (time) * x_offset;

    float y_offset = 0.1;
    gl_Position.y += (time) * y_offset;

    // Rotations (based on z axis)
    float angle = (time) / -10;
    float origX = gl_Position.x;
    float origY = gl_Position.y;
    gl_Position.x = origX * cos(angle) - origY * sin(angle);
    gl_Position.y = origY * cos(angle) + origX * sin(angle);

    shaderColor = vertexColor;
    mainTexCoord = vertexTexCoord;
    landDispTexCoord = vertexTexCoord;
}
