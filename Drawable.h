#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Mesh.h"

class Drawable
{
public:
	Mesh mesh;

	VAO VAO;
	VBO VBO;
	EBO EBO;

	glm::mat4 rotationMatrix;

	Drawable(Mesh& mesh);

	void Draw(Shader& shader, Camera& camera);
	void ApplyRotation(float angleDeltaX, float angleDeltaY);
};

#endif // !DRAWABLE_H
