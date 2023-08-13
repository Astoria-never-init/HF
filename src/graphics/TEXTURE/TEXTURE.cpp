#include "TEXTURE.h"
//#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

bool TEXTURE::CreateTexture(unsigned char* data, int w, int h, int cnt, GLenum slot)
{
	if (!data) { std::cout << "\nError stb"; return false; }
	
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	TEXTURE::slot = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	switch (cnt)
	{
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		break;

	default:
		break;
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	Unbind();
}

void TEXTURE::Bind()
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void TEXTURE::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TEXTURE::Delete()
{
	glDeleteTextures(1, &ID);
}