#ifndef IMGUI_WINDOW_BASE_H
#define IMGUI_WINDOW_BASE_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>

class ImGuiWindowBase {
protected:
	std::string name;
	int width;
	int height;
	float positionX;
	float positionY;
	ImGuiWindowFlags flags;

	// should be called every main loop start
	static void BeginFrame();
	// should be called every main loop end
	static void EndFrame();

public:
	
	ImGuiWindowBase(std::string name, int width, int height, float positionX, float positionY);
	
	virtual void Draw() = 0;

	// Should be called at the end of the program
	void Destroy();
	
};


#endif // !IMGUI_WINDOW_BASE_H