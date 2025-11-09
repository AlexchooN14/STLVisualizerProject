#include "Mesh.h"


Mesh::Mesh(std::vector<Vertex>& vertices) {
	this->vertices = vertices;
	this->centroid = calculateCentroid();
}

glm::vec3 Mesh::calculateCentroid() {
	glm::vec3 centroid(0.0f);
	for (Vertex& vertex : this->vertices) {
		centroid += vertex.getPosition();
	}
	centroid /= static_cast<float>(this->vertices.size());

	return centroid;
}
