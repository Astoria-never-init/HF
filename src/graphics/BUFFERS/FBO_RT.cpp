//#include "FBO_RT.h"
//#include <Windows.h>
//
//FBO_RT::~FBO_RT()
//{
//	Delete();
//}
//
//void FBO_RT::Create(unsigned int width, unsigned int height)
//{
//	glGenTextures(1, &ID);
//	Bind();
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ID, 0);
//}
//
//void FBO_RT::Bind()
//{
//	glBindTexture(GL_TEXTURE_2D, ID);
//}
//
//void FBO_RT::Unbind()
//{
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//void FBO_RT::Delete()
//{
//	glDeleteTextures(1, &ID);
//}
