#include "UBO.h"

UBO::UBO(GLsizeiptr size, GLuint bindingPoint) {
	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_UNIFORM_BUFFER, this->ID);
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ID);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UBO::~UBO() {
	glDeleteBuffers(1, &this->ID);
}

void UBO::update(const void* data, GLsizeiptr size, GLintptr offset=0) {
	glBindBuffer(GL_UNIFORM_BUFFER, this->ID);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
