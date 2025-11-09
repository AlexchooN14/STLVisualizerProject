#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <glm/glm.hpp>
#include "Drawable.h"


class InputController {
private:
    GLFWwindow* window;
    Drawable& drawable;

    glm::vec2 rotationVelocity = glm::vec2(0.0f);
    float scalingVelocity = 0.0f;
    glm::vec2 lastMousePosition;
	glm::vec2 mousePositionDelta;

	const float dragSensitivity = 0.02f;
	const float scaleSensitivity = 0.01f;
    bool rotating;
    bool scaling;

    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    void registerInputCallbacks();

public:
    InputController(GLFWwindow* window, Drawable& drawable);

    void update();
};

#endif // !INPUT_CONTROLLER_H
