#version 330 core
out vec4 FragColor;

in vec3 currPos;
in vec3 Normal;

uniform vec4 objectColor;
uniform vec3 camPos;
uniform bool lightsEnabled;

#define MAX_LIGHTS				8
#define LIGHT_TYPE_POINT		0
#define LIGHT_TYPE_DIRECTIONAL	1
#define LIGHT_TYPE_SPOT			2

struct Light {
    vec3 position;
    vec4 color;
    int type;
};

layout(std140) uniform Lights {
    Light lights[MAX_LIGHTS];
    int lightCount;
};

vec4 pointLight(Light light) {
	vec3 lightVector = light.position - currPos;
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

	return objectColor * light.color * (diffuse + ambientStrength * intensity + specular * intensity);
}

vec4 directLight(Light light) {
	float ambientStrength = 0.2f;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(light.position - currPos);
	
	float diffuse = max(dot(normal, lightDirection), 0.0);
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(camPos - currPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularStrength * specularAmount;

	return objectColor * light.color * (diffuse + ambientStrength + specular);
}

vec4 spotLight(Light light) {
	float outerCone = 10.0f;
	float innerCone = 9.0f;
	float ambientStrength = 0.2f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(light.position - currPos);
	
	float diffuse = max(dot(normal, lightDirection), 0.0);
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(camPos - currPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularStrength * specularAmount;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return objectColor * light.color * (diffuse * intensity + ambientStrength + specular * intensity);
}


vec4 calculateLight(Light light) {
	switch (light.type) {
		case LIGHT_TYPE_POINT:
			return pointLight(light);
			break;
		case LIGHT_TYPE_DIRECTIONAL:
			return directLight(light);
			break;
		case LIGHT_TYPE_SPOT:
			return spotLight(light);
			break;
		default:
			return vec4(0.0f);
			break;
	}
}

void main()
{
	if (lightsEnabled) {
		vec4 result = vec4(0.0);
		for (int i = 0; i < lightCount; i++) {
			result += calculateLight(lights[i]);
		}

		// Ambient occlusion based on view angle
		float ao = pow(dot(normalize(Normal), normalize(camPos - currPos)), lightsEnabled && objectColor.w < 1.0 ? 0.3 : 0.8);

		// Clamp so no total black areas
		ao = clamp(ao, 0.3, 1.0);

		if (objectColor.w < 1.0) {
			// Increase brightness for transparent objects
			FragColor = vec4(result.rgb * ao * 2.0f, objectColor.w);
		} else {
			FragColor = vec4(result.rgb * ao, objectColor.w);
		}

	} else {
		FragColor = objectColor;
	}
	
}