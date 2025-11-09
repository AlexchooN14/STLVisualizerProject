#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"
#include <glad/glad.h>
#include <glm/glm.hpp>


class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	glm::vec3 centroid = glm::vec3(0.0f);

	Mesh(std::vector<Vertex>& vertices);

private:
	glm::vec3 calculateCentroid();
};

#endif // !MESH_H
