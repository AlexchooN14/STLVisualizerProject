#include "LightManager.h"
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


LightManager::LightManager(Shader& shaderProgram, std::vector<Light>& lights) :
	lightUBO(sizeof(GpuLightsData), LIGHT_UNIFORM_BLOCK_BINDING_POINT) {

	GLuint blockIndex = glGetUniformBlockIndex(shaderProgram.ID, "Lights");
	glUniformBlockBinding(shaderProgram.ID, blockIndex, LIGHT_UNIFORM_BLOCK_BINDING_POINT);

	if (lights.size() > MAX_LIGHTS) {
		throw std::runtime_error("Reached maximum number of light instances - 8 (eight)");
	}

	this->lights = lights;
	this->lightsEnabledUniformLocation = glGetUniformLocation(shaderProgram.ID, "lightsEnabled");
}

LightManager::LightManager(Shader& shaderProgram) : 
	lightUBO(sizeof(GpuLightsData), LIGHT_UNIFORM_BLOCK_BINDING_POINT) {

	GLuint blockIndex = glGetUniformBlockIndex(shaderProgram.ID, "Lights");
	glUniformBlockBinding(shaderProgram.ID, blockIndex, LIGHT_UNIFORM_BLOCK_BINDING_POINT);

	this->lightsEnabledUniformLocation = glGetUniformLocation(shaderProgram.ID, "lightsEnabled");
}

void LightManager::addlight(glm::vec3 position, glm::vec4 color, int type) {
	if (lights.size() >= MAX_LIGHTS) {
		throw std::runtime_error("Reached maximum number of light instances - 8 (eight)");
	}
	Light newLight = { position, 0.0f, color, type, glm::vec3(0.0f)};
	this->lights.push_back(newLight);
}

void LightManager::addlight(glm::vec3 position, int type) {
	this->addlight(position, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), type);
}

// Synchronize the UBO with the current lights data to the GPU
void LightManager::updateLightBuffer() {
	GpuLightsData data;
	std::copy(this->lights.begin(), this->lights.end(), data.lights);
	data.lightCount = static_cast<int>(this->lights.size());
	this->lightUBO.update(&data, sizeof(GpuLightsData), 0);
}

void LightManager::disableLights() {
	this->isLightsEnabled = false;
	glUniform1i(this->lightsEnabledUniformLocation, this->isLightsEnabled);
}

void LightManager::enableLights() {
	this->isLightsEnabled = true;
	glUniform1i(this->lightsEnabledUniformLocation, this->isLightsEnabled);
}

bool LightManager::getLightsEnabled() {
	return this->isLightsEnabled;
}
