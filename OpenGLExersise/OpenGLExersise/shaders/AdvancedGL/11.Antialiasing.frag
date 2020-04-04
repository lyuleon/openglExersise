#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D screenTextureMS;
void main()
{
	
	vec4 colorSample3 = texture2D(screenTextureMS, TexCoords);
    FragColor = colorSample3;
}