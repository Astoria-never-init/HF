//#include "TEXTURE.h"
////#define STB_IMAGE_IMPLEMENTATION
////#include "stb_image.h"
//#include <iostream>
//
//
//bool TEXTURE::CreateTexture(uint8* data, int w, int h, int cnt, unsigned short type, GLenum slot)
//{
//	TEXTURE::type = type;
//	//stbi_set_flip_vertically_on_load(true);
//
//	if (!data)
//	{
//		return false;
//	}
//	
//
//	glGenTextures(1, &ID);
//	glActiveTexture(GL_TEXTURE0 + slot);
//	TEXTURE::slot = slot;
//	glBindTexture(GL_TEXTURE_2D, ID);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	
//	//cnt == 4 ? GL_RGBA : GL_RGB
//	if (type == 1)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//	}
//	else if (cnt == 4)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//	}
//	else if (cnt == 3)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	}
//	else if (cnt == 1)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
//	}
//	else throw std::invalid_argument("load error - invalid type(not RGBA, RGB, or R)  :(");
//
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	//stbi_image_free(data);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	//std::cout << "\nSTB_Load ok -  " << path;
//}
//
//void TEXTURE::texUnit(Shader & shader, const char * uniform, GLuint unit)
//{
//	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
//	shader.Activate();
//	glUniform1i(texUni, unit);
//}
//
//void TEXTURE::Bind()
//{
//	glActiveTexture(GL_TEXTURE0 + slot);
//	glBindTexture(GL_TEXTURE_2D, ID);
//}
//
//void TEXTURE::Unbind()
//{
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//void TEXTURE::Delete()
//{
//	glDeleteTextures(1, &ID);
//}
//
//