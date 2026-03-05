#version 330 core

in vec3 shaderColor;
in vec2 mainTexCoord;
in vec2 landDispTexCoord;
uniform sampler2D mainTexture;
uniform sampler2D landDisplacementTexture;
uniform float time;
out vec4 fragmentColor;

void main()
{
    vec4 main = texture(mainTexture, mainTexCoord);

    vec2 landDisp = landDispTexCoord;
    landDisp.y += sin(landDisp.x * 1.2 + time * 1.5) * 0.5;
    landDisp.x *= (1/main.r)*0.2;
    vec4 land = texture(landDisplacementTexture, landDisp);

    

    fragmentColor = vec4(shaderColor, 1.0f) * 
        mix(main, land, time);
}