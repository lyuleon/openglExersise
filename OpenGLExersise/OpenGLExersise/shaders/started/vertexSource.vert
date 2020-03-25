#version 330 core
//layout (location = 0) in vec4 aPos;
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
  gl_Position = projMat*viewMat*modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
  //gl_Position = vec4(aPos.x, aPos.y, aPos.z, aPos.w);
  TexCoord = aTexCoord;
}