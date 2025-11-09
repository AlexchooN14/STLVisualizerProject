#include "Drawable.h"


Drawable::Drawable(Mesh& mesh) : mesh(mesh), VBO(mesh.vertices) {
	this->rotationMatrix = glm::mat4(1.0f);
	this->rotationQuaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	this->scalingMatrix = glm::mat4(1.0f);
	this->VAO.bind();

	// Links VBO to VAO
	this->VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	this->VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO.unbind();
	VBO.unbind();
}

void Drawable::draw(Shader& shader, Camera& camera) {
	shader.activate();
	this->VAO.bind();

	glm::mat4 model = glm::mat4(1.0f);

	// Translate to origin (center the object)
	model = glm::translate(model, -this->mesh.centroid);

	// Rotate
	model *= this->rotationMatrix;

	// Translate back to original position
	model = glm::translate(model, this->mesh.centroid);

	model *= this->scalingMatrix;

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glm::vec3 cameraPosition = camera.getPosition();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), cameraPosition.x, cameraPosition.y, cameraPosition.z);
	camera.uploadMatrix(shader, "camMatrix");

	glDrawArrays(GL_TRIANGLES, 0, this->mesh.vertices.size());
}

void Drawable::applyRotation(float angleDeltaX, float angleDeltaY) {
	glm::quat yaw = glm::angleAxis(angleDeltaX, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat pitch = glm::angleAxis(angleDeltaY, glm::vec3(1.0f, 0.0f, 0.0f));

	this->rotationQuaternion = glm::normalize(yaw * pitch * this->rotationQuaternion);

	this->rotationMatrix = glm::mat4_cast(this->rotationQuaternion);
}

void Drawable::applyScaling(float scale) {
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	this->scalingMatrix *= scaleMatrix;
}
