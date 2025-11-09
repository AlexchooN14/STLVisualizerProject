#ifndef COLOR_PICKER_WINDOW_H
#define COLOR_PICKER_WINDOW_H


#include "ImGuiWindowBase.h"
#include <glm/glm.hpp>
#include "glad/glad.h"


class OptionsWindow : public ImGuiWindowBase {
private:
	GLint objectColorUniform;
	ImVec4 objectColor;
	bool transparencyEnabled = false;
	bool wireframeEnabled = false;

public:
	OptionsWindow(std::string name, GLint objectColorUniform, int width, int height, float positionX, float positionY);

	void draw(Scene* scene) override;
	bool isTransparencyEnabled();
	bool isWireframeEnabled();
};

#endif // !COLOR_PICKER_WINDOW_H
