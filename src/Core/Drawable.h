#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "VAO.h"
#include "VBO.h"
#include "Mesh.h"
#include "Camera.h"


class Drawable {
private:
	VAO VAO;
	VBO VBO;

	// Here I decided to store a copy of the mesh inside the drawable, because the copy is negligible in both CPU time and memory
	// and this enables the Drawable to be more self-contained - it owns its own mesh data
	Mesh mesh;

	glm::quat rotationQuaternion;
	glm::mat4 rotationMatrix;
	glm::mat4 scalingMatrix;

public:
	Drawable(Mesh& mesh);

	void draw(Shader& shader, Camera& camera);
	void applyRotation(float angleDeltaX, float angleDeltaY);
	void applyScaling(float scale);
};

#endif // !DRAWABLE_H
