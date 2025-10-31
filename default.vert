#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 currPos;
out vec3 Normal;
out vec3 color;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	//currPos = vec3(model * vec4(aPos, 1.0f));
	vec4 worldPos = model * vec4(aPos, 1.0);
    currPos = worldPos.xyz;

	Normal = mat3(transpose(inverse(model))) * aNormal;

	color = aColor;

	gl_Position = camMatrix * worldPos;
}