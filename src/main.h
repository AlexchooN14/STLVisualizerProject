#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <optional>
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
#include "FileChoiceDialog.h"
#include "StartupWindow.h"


typedef enum AppState {
    Startup,
    Loading,
    Main,
    Exit
} AppState;

GLFWwindow* window;
ImGuiIO io;
int monitorWidth;
int monitorHeight;
AppState appState = Startup;

void initApplication();
std::string getExecutableDir();

#endif // !MAIN_H
