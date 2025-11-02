#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>


class Vertex {
public:

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	//glm::vec2 texUV;

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color);
	Vertex(glm::vec3 position, glm::vec3 normal);
	Vertex(float vertex[3], float normalVector[3]);
};

#endif // !VERTEX_H
