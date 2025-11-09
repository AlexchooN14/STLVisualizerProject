#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"


class VAO {
public:
	// ID reference for the Vertex Array Object
	GLuint ID;

	VAO();

	// Links a VBO to the VAO using a certain layout
	void linkAttribute(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();
	void destroy();
};

#endif // !VAO_CLASS_H
