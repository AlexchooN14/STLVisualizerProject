#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "shaderClass.h"


class Camera {
private:
	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	glm::vec3 eye = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 center = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 direction = glm::normalize(eye - center);
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
	glm::vec3 up = glm::normalize(glm::cross(direction, right));

	int width;
	int height;

public:
	Camera(glm::vec3 position, int width, int height);

	// Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

	// Exports the camera matrix to a shader
	void uploadMatrix(Shader& shader, const char* uniform);

	glm::vec3 getPosition();
};

#endif // !CAMERA_H
