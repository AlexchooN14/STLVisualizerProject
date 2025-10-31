#include "Vertex.h"

Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color) {
	this->position = position;
	this->normal = normal;
	this->color = color;
}

Vertex::Vertex(float vertex[3], float normal[3]) {
	this->position = glm::vec3(vertex[0], vertex[1], vertex[2]);
	this->normal = glm::vec3(normal[0], normal[1], normal[2]);
	this->color = glm::vec3(0, 0, 0);
}