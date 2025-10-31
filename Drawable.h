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

	float rotationAngle;

	Drawable(Mesh& mesh);

	void Draw(Shader& shader, Camera& camera);
	void ApplyRotation(float angleDelta);
};

#endif // !DRAWABLE_H
