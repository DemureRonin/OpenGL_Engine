#pragma vertex 
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

struct Interpolators {
	//vec3 ViewPosition;
	vec3 WorldPosition;
	vec4 LocalPosition;
	vec3 Normal;
	vec2 UV;
};

out Interpolators interpolators;


uniform mat4 Mmat4;
uniform mat4 Vmat4;
uniform mat4 MVmat4;
uniform mat4 MVPmat4;
uniform vec3 lightDirection;

void main()
{
	interpolators.LocalPosition = vec4(aPos, 1.0);
	interpolators.WorldPosition = vec3(Mmat4 * interpolators.LocalPosition);
	//interpolators.ViewPosition = vec3(Vmat4 * interpolators.WorldPosition);
	interpolators.Normal = mat3(transpose(inverse(Mmat4))) * aNormal;
	interpolators.UV = aUV;
	gl_Position = MVPmat4 * vec4(aPos, 1.0);
}

#pragma fragment
#version 330 core
#define NR_POINT_LIGHTS 1
struct Material {
	sampler2D texture;
	float shininess;
	vec4 tint;
};

struct DirectionalLight {

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
struct Interpolators {

	vec3 WorldPosition;
	vec4 LocalPosition;
	vec3 Normal;
	vec2 UV;
};

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 cameraPosition;

in Interpolators interpolators;

out vec4 FragColor;
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 cameraPosition);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPosition, vec3 cameraPosition);
void main()
{
	vec3 norm = normalize(interpolators.Normal);
	vec3 viewDir = normalize(cameraPosition - interpolators.WorldPosition);

	// phase 1: Directional lighting
	vec3 result = CalcDirLight(directionalLight, norm, viewDir);
	// phase 2: Point lights
	/**for(int i = 0; i < NR_POINT_LIGHTS; i++)
	result += CalcPointLight(pointLights[i], norm, interpolators.WorldPosition, viewDir);*/
	// phase 3: Spot light
	//result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    

	vec4 tex = texture(material.texture, interpolators.UV);
	FragColor = vec4(result, 1.0) * material.tint;
	
	
}
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 cameraPosition)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(cameraPosition, reflectDir), 0.0), material.shininess);
	// combine results
	vec3 ambient  = light.ambient;
	vec3 diffuse  = light.diffuse * diff;
	vec3 specular = light.specular * spec;
	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPosition, vec3 cameraPosition)
{
	vec3 lightDir = normalize(light.position - worldPosition);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(cameraPosition, reflectDir), 0.0), material.shininess);
	// attenuation
	float distance    = length(light.position - worldPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
	light.quadratic * (distance * distance));
	// combine results
	vec3 ambient  = light.ambient;
	vec3 diffuse  = light.diffuse;
	vec3 specular = light.specular;
	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
} 