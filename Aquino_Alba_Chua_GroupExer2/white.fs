#version 330 core

in vec3 shaderColor;
in vec2 mainTexCoord;
in vec2 javaTexCoord;

uniform sampler2D mainTexture;
uniform sampler2D javaTexture;
uniform float time;

out vec4 fragmentColor;

void main()
{
    vec4 main = texture(mainTexture, mainTexCoord);

    vec2 displacedCoord = javaTexCoord;

    displacedCoord.x += sin(javaTexCoord.y * 12.0 + time * 2.0) * 0.03; // same displacement except sin
    displacedCoord.y += cos(javaTexCoord.x * 12.0 + time * 2.0) * 0.03; // same displacement except cos

    vec4 java = texture(javaTexture, displacedCoord);

    fragmentColor = vec4(shaderColor, 1.0) * mix(main, java, time);
}