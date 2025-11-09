#ifndef IMGUI_WINDOW_BASE_H
#define IMGUI_WINDOW_BASE_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>


class Scene;

class ImGuiWindowBase {
protected:
	std::string name;
	int width;
	int height;
	float positionX;
	float positionY;
	ImGuiWindowFlags flags;

	// should be called every main loop start
	static void beginFrame();
	// should be called every main loop end
	static void endFrame();

public:
	
	ImGuiWindowBase(std::string name, int width, int height, float positionX, float positionY);
	
	virtual void draw(Scene* scene) = 0;

	// Should be called at the end of the program
	void destroy();
};

#endif // !IMGUI_WINDOW_BASE_H
