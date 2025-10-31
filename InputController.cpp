#include "InputController.h"


void InputController::Update(GLFWwindow* window, Drawable& drawable) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        glm::vec2 currentMousePosition(mouseX, mouseY);

        if (!this->rotating) {
            this->rotating = true;
            lastMousePosition = currentMousePosition;
        }
        else {
            glm::vec2 delta = currentMousePosition - this->lastMousePosition;
            float angleDelta = delta.x * sensitivity;

            drawable.ApplyRotation(angleDelta);
            rotationVelocity = angleDelta;
            lastMousePosition = currentMousePosition;
        }
    } else {
        this->rotating = false;

        // Apply inertia if there is velocity
        if (std::abs(rotationVelocity) > 0.0001f) {
            drawable.ApplyRotation(rotationVelocity);
            rotationVelocity *= 0.97f; // damping
        } else {
			rotationVelocity = 0.0f;
        }
    }
}