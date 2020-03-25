#version 330 core
in vec2 TexCoord;

uniform sampler2D ourWall;
uniform sampler2D ourFace;
uniform float alpha;

out vec4 FragColor;

void main()
{
   FragColor = mix(texture(ourWall,TexCoord) , texture(ourFace,TexCoord),alpha);
}
