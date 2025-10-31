#include "Drawable.h"
#include <glm/glm.hpp>

Drawable::Drawable(Mesh& mesh) : mesh(mesh), VBO(mesh.vertices), EBO() {
	this->rotationAngle = 0.0f;
	this->VAO.Bind();

	// Links VBO to VAO
	this->VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	this->VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	this->VAO.LinkAttribute(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	//this->VAO.LinkAttribute(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
}

void Drawable::Draw(Shader& shader, Camera& camera) {
	shader.Activate();
	this->VAO.Bind();

	glm::mat4 model = glm::mat4(1.0f);

	// Translate to origin (center the object)
	model = glm::translate(model, -this->mesh.centroid);

	// Rotate around Y-axis
	model = glm::rotate(model, this->rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

	// Translate back to original position
	model = glm::translate(model, this->mesh.centroid);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
	camera.Matrix(shader, "camMatrix");

	glDrawArrays(GL_TRIANGLES, 0, this->mesh.vertices.size());
}

void Drawable::ApplyRotation(float angleDelta) {
	rotationAngle += angleDelta;
	(rotationAngle > 360) ? rotationAngle /= 360.0f : 0;
}