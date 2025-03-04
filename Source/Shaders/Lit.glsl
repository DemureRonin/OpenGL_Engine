#pragma vertex 
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBiTangent;

struct Interpolators {
	//vec3 ViewPosition;
	vec3 WorldPosition;
	vec4 LocalPosition;
	vec3 Normal;
	vec2 UV;
	vec3 Tangent;
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
	interpolators.Tangent = vec3(aTangent.xyz);
	interpolators.Normal = mat3(transpose(inverse(Mmat4))) * aNormal;
	interpolators.UV = aUV;
	gl_Position = MVPmat4 * vec4(aPos, 1.0);
}

#pragma fragment
#version 330 core
#define NR_POINT_LIGHTS 1
#define MAX_SMOOTHNESS_EXPONENT 512
struct Material {
	sampler2D albedo;
	sampler2D normal;
	float shininess;
	vec4 tint;
	float metallicProperty;
	float normalScale;
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
	vec3 Tangent;
};

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 cameraPosition;

in Interpolators interpolators;

out vec4 FragColor;
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 cameraPosition, vec4 specularMap, vec4 albedo);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPosition, vec3 cameraPosition);
float OneMinusReflectivityFromMetallic(float metallic);
vec3 DiffuseAndSpecularFromMetallic(vec3 albedo, float metallic, out vec3 specColor, out float oneMinusReflectivity);
vec3 InitializeFragmentNormal(vec3 normal);
vec3 ComputeSphericalHarmonicsBasis(vec3 normal);
void main() {
	vec3 normal = InitializeFragmentNormal(interpolators.Normal);
	vec3 lightDir = normalize(directionalLight.direction);
	vec4 lightColor = vec4(directionalLight.diffuse, 1);

	float smoothness = mix(0.0001, MAX_SMOOTHNESS_EXPONENT, material.shininess);
	vec4 albedoTex = texture(material.albedo, interpolators.UV) * material.tint;
	

	vec3 specularTint = mix(vec3(1, 1, 1), albedoTex.rgb, material.metallicProperty); // MetallicProperty
	float oneMinusReflectivity;
	vec3 albedo = DiffuseAndSpecularFromMetallic(albedoTex.rgb, material.metallicProperty, specularTint, oneMinusReflectivity);
	vec4 diffuse = lightColor * vec4(albedo, 1) * max(0.0, dot(lightDir, normal));

	vec3 reflectionDir = reflect(-lightDir, normal);
	vec3 viewDir = normalize(cameraPosition - interpolators.WorldPosition);
	vec3 halfVector = normalize(lightDir + viewDir);
	float specFactor = max(0.0, dot(halfVector, normal));

	specFactor = pow(specFactor, smoothness) * material.shininess;

	vec4 specular = vec4(specularTint, 1.0) * lightColor * specFactor;
	vec4 ambientLight =  vec4(0.18, 0.2, 0.26, 1) * albedoTex;
	
	FragColor =  ambientLight + specular + diffuse;
}

vec3 InitializeFragmentNormal(vec3 normal) {
	float normalScale = 0.1;
	vec3 normalMap = (texture(material.normal, interpolators.UV).rgb * 2 - 1);
	normalMap *= normalScale;

	vec3 bitangent = cross(interpolators.Normal, interpolators.Tangent);
	
	mat3 TBN = mat3(normalize(interpolators.Tangent), normalize(bitangent), normalize(interpolators.Normal));
	vec3 normalMapWorldSpace = normalize(TBN * normalMap);
	return normalMapWorldSpace;
}

float OneMinusReflectivityFromMetallic(float metallic) {
	float oneMinusDielectricSpec = 1.0 - 0.04;
	return oneMinusDielectricSpec - metallic * oneMinusDielectricSpec;
}

vec3 DiffuseAndSpecularFromMetallic(
	vec3 albedo, float metallic,
out vec3 specColor, out float oneMinusReflectivity
) {
	specColor = mix(vec3(0.04), albedo, metallic);
	specColor = mix(vec3(1.0), specColor, metallic);
	oneMinusReflectivity = OneMinusReflectivityFromMetallic(metallic);
	return albedo * oneMinusReflectivity;
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 cameraPosition, vec4 specularMap, vec4 albedo)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(cameraPosition, reflectDir), 0.0), material.shininess);
	// combine results
	vec3 ambient = light.ambient * albedo.xyz;
	vec3 diffuse = light.diffuse * diff * albedo.xyz;
	vec3 specular = light.specular * spec * specularMap.xyz;
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
	float distance = length(light.position - worldPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
	light.quadratic * (distance * distance));
	// combine results
	vec3 ambient = light.ambient;
	vec3 diffuse = light.diffuse;
	vec3 specular = light.specular;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
} 