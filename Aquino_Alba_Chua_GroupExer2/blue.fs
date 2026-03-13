#version 330 core

in vec3 shaderColor;
in vec2 mainTexCoord;
in vec2 iceTexCoord;

uniform sampler2D mainTexture;
uniform sampler2D iceTexture;
uniform float time;

out vec4 fragmentColor;

void main()
{
    vec4 main = texture(mainTexture, mainTexCoord);

    vec2 movingCoord = iceTexCoord;

    movingCoord.x += sin(time + iceTexCoord.y * 6.0) * 0.1; // slide x axis
    movingCoord.y += time * 0.1; // slight slide to y

    vec4 ice = texture(iceTexture, movingCoord);

    fragmentColor = vec4(shaderColor, 1.0) * mix(main, ice, time);
}