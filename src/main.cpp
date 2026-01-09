#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "main.h"


int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	initApplication();

	std::string baseDir = getExecutableDir();

	std::string vertexShaderPath = baseDir + "/assets/shaders/default.vert";
	std::string fragmentShaderPath = baseDir + "/assets/shaders/default.frag";
	std::string stlPath;

	Scene* scene = nullptr;
	Mesh* objectMesh = nullptr;
	Shader* shaderProgram = nullptr;
	std::vector<Vertex> verticesVector;

	StartupWindow startupWindow("Select STL File", 500, 250);
	OptionsWindow* optionsWindow = nullptr;

	// WHILE LOOP
	while (!glfwWindowShouldClose(window) && appState != AppState::Exit)
	{
		// Take care of all GLFW events
		glfwPollEvents();
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (appState) {
			case AppState::Startup:
			{
				if (argc < 2) {
					startupWindow.draw();
					if (!startupWindow.getFilePath().empty()) {
						stlPath = startupWindow.getFilePath();
						appState = AppState::Loading;
					}
				}
				else {
					stlPath = argv[1];
					appState = AppState::Loading;
				}
				break;
			}

			case AppState::Loading:
			{
				StlFile stl(stlPath);
				verticesVector = stl.verticesConvertVertexArray();

				objectMesh = new Mesh(verticesVector);
				shaderProgram = new Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

				// What will be drawn, where and how
				scene = new Scene(*objectMesh, window, *shaderProgram, monitorWidth, monitorHeight);

				optionsWindow = new OptionsWindow("Options Chooser", &scene->lightManager, 
					glGetUniformLocation(shaderProgram->ID, "objectColor"), 300, 400, 10.0f, 10.0f);
				// Let the scene handle the gui window
				scene->addGuiWindow(optionsWindow);
				scene->activate();

				appState = AppState::Main;
				break;
			}

			case AppState::Main:
			{
				if (!io.WantCaptureMouse) {
					scene->handleInput();
				}

				scene->draw();

				break;
			}
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
	}

	if (scene) delete scene;
	if (optionsWindow) delete optionsWindow;
	if (shaderProgram) delete shaderProgram;
	if (objectMesh) delete objectMesh;
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

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	monitorWidth = mode->width;
	monitorHeight = mode->height;
	window = glfwCreateWindow(monitorWidth, monitorHeight, "STL_Previewer", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMaximizeWindow(window);

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
	glViewport(0, 0, monitorWidth, monitorHeight);

	// To enable transparency
	glEnable(GL_DEPTH_TEST);
}

std::string getExecutableDir() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return std::filesystem::path(buffer).parent_path().string();
}
