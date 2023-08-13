#ifndef RENDER_TEXTURE_CLASS_H
#define RENDER_TEXTURE_CLASS_H

#include "BASE_BUFFER.h"
#include <glad/glad.h>

class TEXTURE// : public BUFFER
{
public:

	GLuint ID;
	GLenum slot;



	bool CreateTexture(unsigned char* data, int w, int h, int cnt, GLenum slot);
	void Bind();
	void Unbind();
	void Delete();

};

#endif