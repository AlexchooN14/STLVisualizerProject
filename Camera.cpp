#include "Camera.h"

Camera::Camera(glm::vec3 position, int width, int height) {
	this->position = position;
	this->width = width;
	this->height = height;
}
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(this->position, this->position + this->orientation, this->up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(this->width / this->height), nearPlane, farPlane);

	this->cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(this->cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		this->position += this->speed * this->orientation;
	} 
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		this->position += this->speed * -glm::normalize(glm::cross(this->orientation, this->up));
	} 
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		this->position += this->speed * -this->orientation;
	} 
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		this->position += this->speed * glm::normalize(glm::cross(this->orientation, this->up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		this->position += this->speed * this->up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		this->position += this->speed * -this->up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		this->speed = 0.4f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		this->speed = 0.1f;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = this->sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = this->sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(this->orientation, glm::radians(-rotX), glm::normalize(glm::cross(this->orientation, this->up)));
		newOrientation = glm::rotate(this->orientation, glm::radians(-rotY), this->up);
		// Decides whether or not the next vertical Orientation is legal or not
		/*if (abs(glm::angle(newOrientation, this->up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{*/
			this->orientation = newOrientation;
		//}
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}