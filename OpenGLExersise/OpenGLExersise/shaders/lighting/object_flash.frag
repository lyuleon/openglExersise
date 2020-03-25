#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	//��Դ����Ϣ
	vec3  direction;
	float cutOff;
	float outerCutOff;
};

uniform Light light;
uniform Material material;
uniform vec3 viewPos;
void main()
{
	//flash area
    vec3 lightDir = normalize(light.position - FragPos);
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-light.direction)); 
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec4 color;
	// ambient
    vec3 ambient = light.ambient *  vec3(texture(material.diffuse, TexCoords));
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse* diff *  vec3(texture(material.diffuse, TexCoords));
    
	//specular light
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir =reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    //vec3 result = (ambient + diffuse+ specular);
    color  = vec4((ambient + diffuse+ specular)*intensity,1.0);

    FragColor = color;
} 