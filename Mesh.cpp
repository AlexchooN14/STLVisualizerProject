#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
	this->vertices = vertices;
	this->indices = indices;
	this->centroid = calculateCentroid(vertices);
}

Mesh::Mesh(std::vector<Vertex>& vertices) {
	this->vertices = vertices;
	this->centroid = calculateCentroid(vertices);
}

glm::vec3 Mesh::calculateCentroid(std::vector<Vertex>& vertices) {
	glm::vec3 centroid(0.0f);
	for (const auto& v : vertices) {
		centroid += v.position;
	}
	centroid /= static_cast<float>(vertices.size());

	return centroid;
}