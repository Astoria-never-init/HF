#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "VBO.h"
#include "BASE_BUFFER.h"

class VAO : public BUFFER
{
public:
	void init();

	~VAO();
	void LinkAttrib(VBO& vbo, unsigned int layout, unsigned int numComponents, unsigned int type, signed long  int stride, void* offset);

	void Bind() override;
	void Unbind() override;
	void Delete() override;
};

#endif