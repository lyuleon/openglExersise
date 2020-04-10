#version 330 core
struct DirLight  {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
struct SpotLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	//��Դ����Ϣ
	vec3  direction;
	float cutOff;
	float outerCutOff;
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

in vec2 TexCoords;
in vec3 FragPos;
in mat3 TBN;
//��Դ��Ϣ+�����λ�� ͨ��main����
uniform vec3 viewPos;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

//mesh.draw glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform float shininess;

out vec4 FragColor;
void main()
{    

	vec3 normal = texture(texture_normal1, TexCoords).rgb;
    // ����������ת��Ϊ��Χ[-1,1]
    normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN * normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    // ��һ�׶Σ��������
    vec3 result = CalcDirLight(dirLight, normal, viewDir);
    // �ڶ��׶Σ����Դ
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], normal, FragPos, viewDir);    
    // �����׶Σ��۹�
    result += CalcSpotLight(spotLight, normal, FragPos, viewDir);    
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);
	// ��������ɫ
    float diff = max(dot(normal, lightDir), 0.0);
    // �������ɫ
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // �ϲ����
    vec3 ambient  = light.ambient  * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(0.5);
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // ��������ɫ
    float diff = max(dot(normal, lightDir), 0.0);
    // �������ɫ
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // ˥��
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                 light.quadratic * (distance * distance));    
    // �ϲ����
    vec3 ambient  = light.ambient  * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(0.5f);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	 vec3 lightDir = normalize(light.position - fragPos);
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-light.direction)); 
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir =reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 ambient = light.ambient *  vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse* diff *  vec3(texture(texture_diffuse1, TexCoords));
	vec3 specular = light.specular * spec * vec3(0.5f);

    return (ambient + diffuse+ specular)*intensity ;
}