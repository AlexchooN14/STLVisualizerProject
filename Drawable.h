#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Mesh.h"

class Drawable
{
private:
	VAO VAO;
	VBO VBO;
	EBO EBO;

	glm::quat rotationQuaternion;
	glm::mat4 rotationMatrix;
	glm::mat4 scalingMatrix;

public:
	Mesh mesh;

	Drawable(Mesh& mesh);

	void Draw(Shader& shader, Camera& camera);
	void ApplyRotation(float angleDeltaX, float angleDeltaY);
	void ApplyScaling(float scale);
};

#endif // !DRAWABLE_H
