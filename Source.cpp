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

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "OptionsWindow.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


GLFWwindow* window;
ImGuiIO io;

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int main()
{
	StlFile stl = StlFile("stl_file.STL");
	std::vector<Vertex> verticesVector = stl.verticesConvertVertexArray();

	initApplication();

	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	Mesh objectMesh(verticesVector);
	Drawable drawable(objectMesh);
	InputController input(window, drawable);

	shaderProgram.Activate();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.01f, 0.02f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glm::vec3 originPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, originPosition);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glEnable(GL_DEPTH_TEST);

	Camera camera(glm::vec3(0.0f, 0.0f, 2.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	camera.updateMatrix(45.0f, 0.1f, 100.0f);

	OptionsWindow OptionsWindow("Options Chooser", glGetUniformLocation(shaderProgram.ID, "objectColor"), 300, 400, 10.0f, 10.0f);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!io.WantCaptureMouse) {
			input.Update();
		}
		drawable.Draw(shaderProgram, camera);
		
		OptionsWindow.Draw();
		// std::cout << OptionsWindow.isTransparencyEnabled() << std::endl;

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}


	OptionsWindow.Destroy();

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
