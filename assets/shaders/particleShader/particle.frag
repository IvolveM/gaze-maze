#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D sprite;
uniform vec4 color;

void main()
{
    vec4 texColor = (texture(sprite, TexCoord)); // * color
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}  
