#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D floorTexture;
void main()
{           
    //FragColor = vec4(texture(floorTexture, TexCoords).rgb, 1.0);
    FragColor = vec4(0,0.5,0.5,1.0);
}