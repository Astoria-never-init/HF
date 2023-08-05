#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "VBO.h"
#include "BASE_BUFFER.h"
#include<glad/glad.h>

class VAO : public BUFFER
{
public:
	void init();

	~VAO();
	void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind() override;
	void Unbind() override;
	void Delete() override;
};

#endif