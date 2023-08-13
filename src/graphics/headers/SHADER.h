#ifndef RENDER_SHADER_CLASS_H
#define RENDER_SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>

class Shader
{
public:
	GLuint ID;

	Shader() {};

	bool AddShader(const char* _source_code, int _type, std::string* _log = 0x0);
	bool Create(std::string* _log = 0x0);
	void Activate();
	void Delete();

	void bindAttribute(GLuint index, const std::string& name);
	void setFloat(const std::string name, float value);
	void setInt(const std::string name, int value);
	void setTexture2D(const std::string name, GLuint texture);
	void setMat4(const std::string name, glm::mat4 matrix);
	void setVec4(const std::string name, glm::vec4 vec4);
	void setVec3(const std::string name, glm::vec3 vec3);
	void setVec2(const std::string name, glm::vec2 vec2);

private:
	std::vector<GLuint> shaders;
	bool compileErrors(unsigned int _shader, int _type, std::string* _log = 0x0);
	GLuint getLocation(const std::string& name);
};


#endif