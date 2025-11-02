#include "OptionsWindow.h"
#include "ImGuiWindowBase.h"
#include "glad/glad.h"


OptionsWindow::OptionsWindow(std::string name, GLint objectColorUniform, int width, int height, float positionX, float positionY) :
	ImGuiWindowBase(name, width, height, positionX, positionY) {

	this->objectColorUniform = objectColorUniform;
	this->objectColor = ImVec4((69.0f / 255.0f), (161.0f / 255.0f), (204.0f / 255.0f), 1.0f);
	this->flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
}

bool OptionsWindow::isTransparencyEnabled() {
	return this->transparencyEnabled;
}

void OptionsWindow::Draw() {
	// Obligatory call
	this->BeginFrame();

	ImGui::SetNextWindowSize(ImVec2(this->width, this->height), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2(this->positionX, this->positionY), ImGuiCond_Always);

	ImGui::Begin(this->name.c_str(), nullptr, this->flags);

	if (ImGui::Button("Transparency")) {
		this->transparencyEnabled = !this->transparencyEnabled;
		this->wireframeEnabled = false;
	}

	if (ImGui::Button("Wireframe")) {
		this->wireframeEnabled = !this->wireframeEnabled;
		this->transparencyEnabled = false;
	}

	// ImGui::Text("This is some useful text.");
	/*ImGui::SliderFloat("HUE", &this->hue, 0.0f, 255.0f);
	glUniform4f(this->objectColorUniform, objectColor.x, lightColor.y, lightColor.z, lightColor.w);*/
	ImGui::ColorEdit3("Object Color", (float*)&this->objectColor);

	if (this->transparencyEnabled) {
		glUniform4f(this->objectColorUniform, this->objectColor.x, this->objectColor.y, this->objectColor.z, 0.3f);
	} else {
		glUniform4f(this->objectColorUniform, this->objectColor.x, this->objectColor.y, this->objectColor.z, this->objectColor.w);
	}

	if (this->wireframeEnabled) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	ImGui::End();

	// Obligatory call
	this->EndFrame();
}