#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 texCoords;
} gs_in[];

out vec2 TexCoords; 
out vec3 fColor;

uniform float time;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
vec4 explode(vec4 position, vec3 normal)
{
    float magnitude =2;
    vec3 direction = normal * ((sin(time) + 1.0) * 0.5) * magnitude; 
    return position + vec4(direction, 0.0);
}

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
 	//vec3 a = vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position);
  //  vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position);
    return normalize(cross(a, b));
}

void main() {
	//vec3 normal = GetNormal();
	//mat4 aa = projection*view*model;
	//gl_Position = aa* explode(gl_in[0].gl_Position, normal);
	//TexCoords = gs_in[0].texCoords;
	//fColor = vec3(1.0f,1.0f,1.0f);
	//EmitVertex();
	//gl_Position = aa*explode(gl_in[1].gl_Position, normal);
	//TexCoords = gs_in[1].texCoords;
	//fColor = vec3(0.0f);
	//EmitVertex();
	//gl_Position = aa*explode(gl_in[2].gl_Position, normal);
	//TexCoords = gs_in[2].texCoords;
	//fColor = vec3(0.5f);
	//EmitVertex();
	//EndPrimitive();

	vec3 normal = GetNormal();
	gl_Position = explode(gl_in[0].gl_Position, normal);
	TexCoords = gs_in[0].texCoords;
	fColor = vec3(1.0f,1.0f,1.0f);
	EmitVertex();
	gl_Position = explode(gl_in[1].gl_Position, normal);
	TexCoords = gs_in[1].texCoords;
	fColor = vec3(0.0f);
	EmitVertex();
	gl_Position = explode(gl_in[2].gl_Position, normal);
	TexCoords = gs_in[2].texCoords;
	fColor = vec3(0.5f);
	EmitVertex();
	EndPrimitive();


	//vec3 normal = GetNormal();
	//gl_Position = explode(gl_in[0].gl_Position, normal);
 //   TexCoords = gs_in[0].texCoords;
 //   EmitVertex();
 //   gl_Position = explode(gl_in[1].gl_Position, normal);
 //   TexCoords = gs_in[1].texCoords;
 //   EmitVertex();
 //   gl_Position = explode(gl_in[2].gl_Position, normal);
 //   TexCoords = gs_in[2].texCoords;
 //   EmitVertex();
 //   EndPrimitive();
}