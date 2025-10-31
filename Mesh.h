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
	
	VAO VAO;
	VBO VBO;
	EBO EBO;

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	Mesh(std::vector<Vertex>& vertices);

	void Draw(Shader& shader, Camera& camera);
};

#endif // !MESH_H
