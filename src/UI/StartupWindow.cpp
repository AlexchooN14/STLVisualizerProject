#include "StartupWindow.h"
#include "FileChoiceDialog.h"


StartupWindow::StartupWindow(std::string name, int width, int height) :
	ImGuiWindowBase(name, width, height, 0, 0) {
	this->flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
}

void StartupWindow::setFilePath(std::string path) {
	this->selectedFilePath = path;
}

std::string StartupWindow::getFilePath() {
	return this->selectedFilePath;
}

void StartupWindow::draw() {
	// Obligatory call
	this->beginFrame();

	ImGuiIO io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(this->width, this->height), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

	ImGui::Begin(this->name.c_str(), nullptr, this->flags);

	ImGui::Text("Choose an STL file to preview.");
	if (ImGui::Button("Choose File")) {
		this->selectedFilePath = OpenFileDialog();
	}

	ImGui::End();

	// Obligatory call
	this->endFrame();
}
