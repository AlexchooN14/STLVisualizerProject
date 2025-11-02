#include "ImGuiWindowBase.h"


// should be called every main loop start
void ImGuiWindowBase::BeginFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

// should be called every main loop end
void ImGuiWindowBase::EndFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImGuiWindowBase::ImGuiWindowBase(std::string name, int width, int height, float positionX, float positionY) {
	this->name = name;
	this->width = width;
	this->height = height;
	this->positionX = positionX;
	this->positionY = positionY;
}

// Should be called at the end of the program
void ImGuiWindowBase::Destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}