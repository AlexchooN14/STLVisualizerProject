#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 currPos;
out vec3 Normal;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	vec4 worldPos = model * vec4(aPos, 1.0);
    currPos = worldPos.xyz;

	Normal = mat3(transpose(inverse(model))) * aNormal;

	gl_Position = camMatrix * worldPos;
}