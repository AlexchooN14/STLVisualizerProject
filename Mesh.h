#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Camera.h"


class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	glm::vec3 centroid = glm::vec3(0.0f);

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	Mesh(std::vector<Vertex>& vertices);

	glm::vec3 calculateCentroid(std::vector<Vertex>& vertices);
};

#endif // !MESH_H
