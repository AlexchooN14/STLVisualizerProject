#include "OptionsWindow.h"
#include <iostream>


OptionsWindow::OptionsWindow(std::string name, LightManager* lightManager, GLint objectColorUniform, int width, int height,
	float positionX, float positionY) : ImGuiWindowBase(name, width, height, positionX, positionY) {

	this->objectColorUniform = objectColorUniform;
	this->objectColor = ImVec4((69.0f / 255.0f), (161.0f / 255.0f), (204.0f / 255.0f), 1.0f);
	this->flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
	this->lightManager = lightManager;
}

bool OptionsWindow::isTransparencyEnabled() {
	return this->transparencyEnabled;
}

bool OptionsWindow::isWireframeEnabled() {
	return this->wireframeEnabled;
}

void OptionsWindow::draw() {
	// Obligatory call
	this->beginFrame();

	ImGui::SetNextWindowSizeConstraints(ImVec2(this->width, 0), ImVec2(this->width, FLT_MAX));
	// ImGui::SetNextWindowSize(ImVec2(this->width, this->height), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2(this->positionX, this->positionY), ImGuiCond_Always);

	ImGui::Begin(this->name.c_str(), nullptr, this->flags);

	// -- SOLID COLOR BUTTON --
	if (!this->transparencyEnabled && !this->wireframeEnabled) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_Button));
	}
	if (ImGui::Button("Solid Color", ImVec2(ImGui::GetContentRegionAvail().x, 30))) {
		this->transparencyEnabled = false;
		this->wireframeEnabled = false;
	}
	ImGui::PopStyleColor();
	// ----------------------

	// -- TRANSPARENCY BUTTON --
	if (this->transparencyEnabled) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_Button));
	}
	if (ImGui::Button("Transparency", ImVec2(ImGui::GetContentRegionAvail().x, 30))) {
		this->transparencyEnabled = !this->transparencyEnabled;
		this->wireframeEnabled = false;
	}
	ImGui::PopStyleColor();
	// ----------------------

	// -- WIREFRAME BUTTON --
	if (this->wireframeEnabled) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
		// Disable lights when in wireframe mode so we can see the wireframe better
		if (this->lightManager->getLightsEnabled()) {
			this->lightManager->disableLights();
		}
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_Button));
		if (!this->lightManager->getLightsEnabled()) {
			this->lightManager->enableLights();
		}
	}
	if (ImGui::Button("Wireframe", ImVec2(ImGui::GetContentRegionAvail().x, 30))) {
		this->wireframeEnabled = !this->wireframeEnabled;
		this->transparencyEnabled = false;
	}
	ImGui::PopStyleColor();
	// ----------------------

	ImGui::ColorEdit3("Color", (float*)&this->objectColor);

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
	this->endFrame();
}
