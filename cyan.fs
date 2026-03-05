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
in vec2 seaTexCoord;

uniform sampler2D mainTexture;
uniform sampler2D seaDisplacement;
uniform float time;
uniform float speed;

out vec4 fragmentColor;

void main()
{   
    // Main Image
    vec4 mainColor = texture(mainTexture, mainTexCoord);
    vec2 seaTexCoordReal = seaTexCoord + time/2;
    vec4 seaColor = texture(seaDisplacement, seaTexCoordReal);

    vec2 mainSeaTexCoord = mainTexCoord * seaColor.r;
    vec4 mainSea = texture(mainTexture, mainSeaTexCoord);
    fragmentColor = vec4(shaderColor, 1.0f) * 
            mix(mainColor, mainSea, sin(time)+1.0f);
}