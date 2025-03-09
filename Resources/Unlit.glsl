#pragma vertex 
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBiTangent;

struct Interpolators {
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
	interpolators.Tangent = vec3(aTangent.xyz);
	interpolators.Normal = mat3(transpose(inverse(Mmat4))) * aNormal;
	interpolators.UV = aUV;
	gl_Position = MVPmat4 * vec4(aPos, 1.0);
}

#pragma fragment
#version 330 core

struct Material {
	sampler2D albedo;
	vec4 tint;
};


struct Interpolators {
	vec3 WorldPosition;
	vec4 LocalPosition;
	vec3 Normal;
	vec2 UV;
	vec3 Tangent;
};


uniform Material material;
uniform vec3 cameraPosition;

in Interpolators interpolators;

out vec4 FragColor;

void main() {
	vec4 tex = texture(material.albedo, interpolators.UV);
	FragColor = tex * material.tint;
}

