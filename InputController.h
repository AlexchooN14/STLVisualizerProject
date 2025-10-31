#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <glm/glm.hpp>
#include "Drawable.h"


class InputController {
public:
    float rotationVelocity = 0.0f;
    glm::vec2 lastMousePosition;
    bool rotating = false;

	float sensitivity = 0.02f;

    void Update(GLFWwindow* window, Drawable& drawable);
};


#endif // !INPUT_CONTROLLER_H
