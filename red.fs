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
        mix(main, land, sin(time)+1.0);
}