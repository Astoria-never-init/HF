//#include "SSBO.h"
//
//SSBO::~SSBO()
//{
//	Delete();
//}
//
//SSBO::SSBO(const void * vertices, GLsizeiptr size, GLuint ShaderBindingLayout)
//{
//	Create(vertices, size, ShaderBindingLayout);
//}
//
//void SSBO::Create(const void * vertices, GLsizeiptr size, GLuint ShaderBindingLayout)
//{
//	glGenBuffers(1, &ID);
//	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
//	glBufferData(GL_SHADER_STORAGE_BUFFER, size, vertices, GL_STATIC_DRAW);
//	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ShaderBindingLayout, ID);
//	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
//}
//
//void SSBO::Bind()
//{
//	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
//}
//
//void SSBO::Unbind()
//{
//	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
//}
//
//void SSBO::Delete()
//{
//	glDeleteBuffers(1, &ID);
//}
//
//void * CreateSsboClass()
//{
//	return new SSBO;
//}
//