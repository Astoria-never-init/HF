#include "headers/FBO.h"
#include <glad/glad.h>

FBO::~FBO()
{
	Delete();
}

void FBO::init()
{
	glGenFramebuffers(1, &ID);
	Bind();
}

void FBO::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void FBO::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Delete()
{
	glDeleteFramebuffers(1, &ID);
}
