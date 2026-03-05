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

    vec2 coord = wolfTexCoord;
    
    // zoom scale
    float zoom = 1.0 + time * 0.3;

    // zoom out from center
    coord = (coord - vec2(0.5)) * zoom + vec2(0.5);

    vec4 wolf = texture(wolfTexture, coord);

    fragmentColor = vec4(shaderColor, 1.0) * mix(main, wolf, time);
}