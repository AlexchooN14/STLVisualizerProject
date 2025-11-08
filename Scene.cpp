#include "Scene.h"
#include "ImGuiWindowBase.h"


Scene::Scene(Mesh& mesh, GLFWwindow* window, Shader& shader) :
	drawable(mesh), inputController(window, drawable), shader(shader), lightManager(shader), camera(glm::vec3(0.0f, 0.0f, 2.0f), SCREEN_WIDTH, SCREEN_HEIGHT) {

	this->camera.updateMatrix(45.0f, 0.1f, 100.0f);
}

Scene::Scene(Mesh& mesh, GLFWwindow* window, Shader& shader, Camera& camera) :
	drawable(mesh), inputController(window, drawable), shader(shader), lightManager(shader), camera(camera) {}

void Scene::activate() {
	this->shader.activate();
	defaultLighting();
}

void Scene::deactivate() {
	this->shader.deactivate();
}

void Scene::enableLighting() {
	this->lightManager.enableLights();
}

void Scene::disableLighting() {
	this->lightManager.disableLights();
}

void Scene::addGuiWindow(ImGuiWindowBase* window) {
	this->guiWindows.push_back(window);
}

// Function to be called every frame to draw the scene
void Scene::draw() {
	for (ImGuiWindowBase* window : this->guiWindows) {
		window->draw(this);
	}

	this->drawable.draw(this->shader, this->camera);
}

// Function to be called every frame to handle input
void Scene::handleInput() {
	this->inputController.update();
}

void Scene::destroy() {
	for (ImGuiWindowBase* window : this->guiWindows) {
		window->destroy();
	}
}

void Scene::defaultLighting() {
	this->lightManager.addlight(glm::vec3(0.0f, 2.0f, 0.0f), LIGHT_TYPE_SPOT);
	this->lightManager.addlight(glm::vec3(-2.0f, 0.0f, 2.0f), LIGHT_TYPE_DIRECTIONAL);
	this->lightManager.addlight(glm::vec3(0.0f, 0.0f, -2.0f), LIGHT_TYPE_POINT);
	this->lightManager.updateLightBuffer();
}
