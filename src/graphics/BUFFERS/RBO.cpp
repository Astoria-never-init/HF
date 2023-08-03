#include "RBO.h"
#include<glad/glad.h>

RBO::~RBO()
{
	Delete();
}

void RBO::Create()
{
	glGenRenderbuffers(1, &ID);
}

void RBO::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
}

void RBO::Unbind()
{
}

void RBO::Delete()
{
}
