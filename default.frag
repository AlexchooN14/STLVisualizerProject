#version 330 core
out vec4 FragColor;

in vec3 color;
in vec3 Normal;
in vec3 currPos;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambientStrength = 0.2f;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - currPos);
	
	float diffuse = max(dot(normal, lightDirection), 0.0);
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(camPos - currPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularStrength * specularAmount;

	FragColor = vec4(color, 1.0f) * lightColor * (diffuse + ambientStrength + specular);
}