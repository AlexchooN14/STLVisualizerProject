#ifndef SCENE_H
#define SCENE_H

#include "Mesh.h"
#include "Drawable.h"
#include "InputController.h"
#include "LightManager.h"
#include <vector>


class ImGuiWindowBase;


class Scene {
public:
	Drawable drawable;
	InputController inputController;
	LightManager lightManager;
	Shader& shader;
	Camera camera;
	std::vector<ImGuiWindowBase*> guiWindows;

	Scene(Mesh& mesh, GLFWwindow* window, Shader& shader, int monitorWidth, int monitorHeight);
	Scene(Mesh& mesh, GLFWwindow* window, Shader& shader, Camera& camera);

	void activate();
	void deactivate();
	void enableLighting();
	void disableLighting();
	void addGuiWindow(ImGuiWindowBase* window);
	// Function to be called every frame to draw the scene
	void draw();
	// Function to be called every frame to handle input
	void handleInput();
	void destroy();

private:
	void defaultLighting();
};

#endif // !SCENE_H
