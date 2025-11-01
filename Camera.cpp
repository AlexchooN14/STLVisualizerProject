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
	projection = glm::perspective(glm::radians(FOVdeg), (float)this->width / (float)this->height, nearPlane, farPlane);

	this->cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(this->cameraMatrix));
}
