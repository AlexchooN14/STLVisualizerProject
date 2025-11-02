#ifndef UBO_H
#define UBO_H

#include <glm/glm.hpp>
#include <glad/glad.h>


class UBO {
private:
	GLuint ID;
	GLuint bindingPoint;
	GLsizeiptr bufferSize;

public:
	UBO(GLsizeiptr size, GLuint bindingPoint);

	void update(const void* data, GLsizeiptr size, GLintptr offset);

	~UBO();

};

#endif // !UBO_H