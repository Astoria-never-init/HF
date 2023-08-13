#include "SHADER.h"
#include <glm/gtc/type_ptr.hpp>

bool Shader::AddShader(const char* _source_code, int _type, std::string* _log)
{
	GLuint shader = glCreateShader(_type);

	glShaderSource(shader, 1, &_source_code, NULL);
	glCompileShader(shader);

	if (!compileErrors(shader, GL_COMPILE_STATUS, _log))
	{
		return false;
	}
	shaders.push_back(shader);
	return true;
}

bool Shader::Create(std::string* _log)
{
	ID = glCreateProgram();

	for (auto & shader : shaders) 
	{
		glAttachShader(ID, shader);
	}
	glLinkProgram(ID);
	if (!compileErrors(ID, GL_LINK_STATUS, _log)) 
	{
		for (auto & shader : shaders)
		{
			glDetachShader(ID, shader);
		}
		return false;
	}
	for (auto & shader : shaders)
	{
		glDeleteShader(shader);
	}
	return true;
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

bool Shader::compileErrors(unsigned int _shader, int _type, std::string* _log)
{
	GLint hasCompiled;
	glGetShaderiv(_shader, _type, &hasCompiled);
	if (hasCompiled == GL_FALSE)
	{
		if (_log) 
		{
			char *log = new char[1024];
			glGetShaderInfoLog(_shader, 1024, NULL, log);
			*_log = log;
			delete[] log;
		}
		return false;
	}
	return true;
}

GLuint Shader::getLocation(const std::string & name)
{
	return glGetUniformLocation(ID, name.c_str());
}

void Shader::bindAttribute(GLuint index, const std::string & name)
{
	glBindAttribLocation(ID, index, name.c_str());
}

void Shader::setFloat(const std::string name, float value)
{
	glUniform1f(getLocation(name), value);
}

void Shader::setInt(const std::string name, int value)
{
	glUniform1i(getLocation(name), value);
}

void Shader::setTexture2D(const std::string name, GLuint texture)
{
	Activate();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	getLocation(name);
	glUniform1f(texture, 0);
}

void Shader::setMat4(const std::string name, glm::mat4 matrix)
{
	Activate();
	glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec4(const std::string name, glm::vec4 vec4)
{
	Activate();
	glUniform4f(getLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::setVec3(const std::string name, glm::vec3 vec3)
{
	Activate();
	glUniform3f(getLocation(name), vec3.x, vec3.y, vec3.z);
}

void Shader::setVec2(const std::string name, glm::vec2 vec2)
{
	Activate();
	glUniform2f(getLocation(name), vec2.x, vec2.y);
}

