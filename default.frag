#version 330 core
out vec4 FragColor;

in vec3 currPos;
in vec3 Normal;

uniform vec4 objectColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight() {
	vec3 lightVector = lightPos - currPos;
	float distance = length(lightVector);
	float a = 3.0f;
	float b = 0.7f;
	float intensity = 1.0f / (a * distance * distance + b * distance + 1.0f);

	float ambientStrength = 0.2f;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVector);
	
	float diffuse = max(dot(normal, lightDirection), 0.0);
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(camPos - currPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularStrength * specularAmount;

	return objectColor * lightColor * (diffuse + ambientStrength * intensity + specular * intensity);
}

vec4 directLight() {
	float ambientStrength = 0.2f;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	
	float diffuse = max(dot(normal, lightDirection), 0.0);
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(camPos - currPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularStrength * specularAmount;

	return objectColor * lightColor * (diffuse + ambientStrength + specular);
}

vec4 spotLight() {
	float outerCone = 0.90f;
	float innerCone = 0.95f;
	float ambientStrength = 0.2f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - currPos);
	
	float diffuse = max(dot(normal, lightDirection), 0.0);
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(camPos - currPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularStrength * specularAmount;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return objectColor * lightColor * (diffuse * intensity + ambientStrength + specular * intensity);
}

void main()
{
	// FragColor = vec4(normalize(Normal) * 0.5 + 0.5, 1.0);
	// FragColor = directLight();
	// Debug
	FragColor = objectColor;
}