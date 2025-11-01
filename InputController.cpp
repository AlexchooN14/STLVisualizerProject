#include "InputController.h"


InputController::InputController(GLFWwindow* window, Drawable& drawable) : window(window), drawable(drawable) {
    this->rotationVelocity = glm::vec2(0.0f);
    this->rotating = false;
    this->scaling = false;

	registerInputCallbacks();
}

void InputController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        this->rotating = true;
        this->lastMousePosition = glm::vec2(mouseX, mouseY);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        this->rotating = false;
    }
}

void InputController::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	this->scaling = true;
    this->scalingVelocity = yoffset * this->scaleSensitivity;
    float scaleFactor = 1.0f + this->scalingVelocity;
    this->drawable.ApplyScaling(scaleFactor);
}

void InputController::registerInputCallbacks() {
    glfwSetScrollCallback(this->window, [](GLFWwindow* window, double xoffset, double yoffset) {
        InputController* controller = static_cast<InputController*>(glfwGetWindowUserPointer(window));
        if (controller) controller->mouseScrollCallback(window, xoffset, yoffset);
        });

    glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods) {
        InputController* controller = static_cast<InputController*>(glfwGetWindowUserPointer(window));
        if (controller) controller->mouseButtonCallback(window, button, action, mods);
        });

    glfwSetWindowUserPointer(this->window, this);
}

void InputController::Update() {
    if (this->rotating) {
        double mouseX, mouseY;
        glfwGetCursorPos(this->window, &mouseX, &mouseY);
        glm::vec2 currentMousePosition(mouseX, mouseY);

        this->mousePositionDelta = currentMousePosition - this->lastMousePosition;
        this->lastMousePosition = currentMousePosition;

        float angleDeltaX = this->mousePositionDelta.x * this->dragSensitivity;
        float angleDeltaY = this->mousePositionDelta.y * this->dragSensitivity;

        this->drawable.ApplyRotation(angleDeltaX, angleDeltaY);
        rotationVelocity = glm::vec2(angleDeltaX, angleDeltaY);
    } 
    else {
        // Inertia and damping functionality for rotation
        if (glm::length(rotationVelocity) > 0.0001f) {
            this->drawable.ApplyRotation(rotationVelocity.x, rotationVelocity.y);
            rotationVelocity *= 0.97f;
        }
        else {
            rotationVelocity = glm::vec2(0.0f);
        }
    }

    if (this->scaling) {
		// Inertia and damping functionality for scaling
        if (std::abs(this->scalingVelocity) > 0.0001f) {
            float scaleFactor = 1.0f + this->scalingVelocity;
            this->drawable.ApplyScaling(scaleFactor);
            this->scalingVelocity *= 0.95f;
        }
        else {
            this->scalingVelocity = 0.0f;
            this->scaling = false;
        }
	}

}