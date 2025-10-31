#include "InputController.h"


void InputController::Update(GLFWwindow* window, Drawable& drawable) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        glm::vec2 currentMousePosition(mouseX, mouseY);

        if (!this->rotating) {
            this->rotating = true;
            lastMousePosition = currentMousePosition;
        }
        else {
            glm::vec2 delta = currentMousePosition - this->lastMousePosition;
            float angleDeltaX = delta.x * sensitivity;
            float angleDeltaY = delta.y * sensitivity;

            drawable.ApplyRotation(angleDeltaX, angleDeltaY);
            rotationVelocity.x = angleDeltaX;
            rotationVelocity.y = angleDeltaY;
            lastMousePosition = currentMousePosition;
        }
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        this->rotating = false;

        // Apply inertia if there is velocity
        if (std::abs(rotationVelocity.x) > 0.0001f || std::abs(rotationVelocity.y) > 0.0001f) {
            drawable.ApplyRotation(rotationVelocity.x, rotationVelocity.y);
            rotationVelocity *= 0.97f; // damping
        } else {
			rotationVelocity = glm::vec2(0.0f);
        }
    }
}