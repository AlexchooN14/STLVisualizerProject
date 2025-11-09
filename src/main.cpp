#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Mesh.h"
#include "stl.h"
#include "Drawable.h"
#include "InputController.h"
#include "OptionsWindow.h"
#include "LightManager.h"
#include "Scene.h"
#include <windows.h>
#include <filesystem>


GLFWwindow* window;
ImGuiIO io;


void initApplication();
std::string getExecutableDir();

int main(int argc, char* argv[])
{
	initApplication();

	std::string baseDir = getExecutableDir();

	std::string vertexShaderPath = baseDir + "/assets/shaders/default.vert";
	std::string fragmentShaderPath = baseDir + "/assets/shaders/default.frag";
	std::string exampleSTLPath = baseDir + "/assets/examples/stl_file.STL";
	std::string iconPath = baseDir + "/assets/icons/icon.ico";


	StlFile stl = StlFile((argc > 1) ? argv[1] : exampleSTLPath);
	std::vector<Vertex> verticesVector = stl.verticesConvertVertexArray();
	
	Mesh objectMesh(verticesVector);
	Shader shaderProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

	// What will be drawn, where and how
	Scene scene = Scene(objectMesh, window, shaderProgram);

	OptionsWindow optionsWindow("Options Chooser", glGetUniformLocation(shaderProgram.ID, "objectColor"), 300, 400, 10.0f, 10.0f);
	// Let the scene handle the gui window
	scene.addGuiWindow(&optionsWindow);
	scene.activate();


	// WHILE LOOP
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		if (!io.WantCaptureMouse) {
			scene.handleInput();
		}

		scene.draw();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	scene.destroy();
	shaderProgram.destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void initApplication() {
	// Initialize GLFW
	glfwInit();
	// Tell GLFW what version of OpenGL we are using 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui::StyleColorsDark();

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "STL_Previewer", glfwGetPrimaryMonitor(), NULL);
	// Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Setup backends once
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// To enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// To enable transparency
	glEnable(GL_DEPTH_TEST);
}

std::string getExecutableDir() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return std::filesystem::path(buffer).parent_path().string();
}
