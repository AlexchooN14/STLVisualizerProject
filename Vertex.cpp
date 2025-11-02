#include "Vertex.h"

Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color) {
	this->position = position;
	this->normal = normal;
	this->color = color;
}

Vertex::Vertex(float vertex[3], float normal[3]) {
	this->position = glm::vec3(vertex[0], vertex[1], vertex[2]);
	this->normal = glm::vec3(normal[0], normal[1], normal[2]);
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);
}

Vertex::Vertex(glm::vec3 position, glm::vec3 normal) {
	this->position = position;
	this->normal = normal;
	// R 69, G 161, B 204
	this->color = glm::vec3((69.0f / 255.0f), (161.0f / 255.0f), (204.0f / 255.0f));
}