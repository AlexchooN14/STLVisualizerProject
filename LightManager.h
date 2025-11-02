#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#define MAX_LIGHTS 8
#define LIGHT_UNIFORM_BLOCK_BINDING_POINT 0

#define LIGHT_TYPE_POINT		0
#define LIGHT_TYPE_DIRECTIONAL	1
#define LIGHT_TYPE_SPOT			2

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "UBO.h"
#include "shaderClass.h"


struct Light {
	glm::vec3 position;
	float _pad1;
	glm::vec4 color;
	int type;
	glm::vec3 _pad2;
};

struct GpuLightsData {
	Light lights[MAX_LIGHTS];
	int lightCount;
	glm::vec3 _pad3;
};


class LightManager {
protected:
	std::vector<Light> lights;
	UBO lightUBO;

public:
	LightManager(Shader& shaderProgram, std::vector<Light> lights);
	LightManager(Shader& shaderProgram);

	void addlight(glm::vec3 position, glm::vec4 color, int type);
	void addlight(glm::vec3 position, int type);
	void updateLights();
};


#endif // !LIGHT_MANAGER_H
