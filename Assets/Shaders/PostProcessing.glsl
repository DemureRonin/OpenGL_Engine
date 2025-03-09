#pragma vertex 
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aUV;
layout (location = 1) in vec3 aNormal;

layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBiTangent;

out vec2 TexCoords;

void main()
{
	TexCoords = aUV;
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}

#pragma fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
	vec3 col = texture(screenTexture, TexCoords).rgb;

	FragColor = vec4(col, 1.0);

} 