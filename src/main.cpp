#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "graphics/headers/VBO.h"
#include "graphics/headers/VAO.h"
#include "graphics/headers/EBO.h"
#include "graphics/headers/SHADER.h"
#include <fstream>

using namespace std;

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

int main()
{
	

	unsigned int X = 1240, Y = 920;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow * window = glfwCreateWindow(X, Y, "ST_BloodEngine Viewport", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(2);
	gladLoadGL();
	glViewport(0, 0, X, Y);

	std::vector<unsigned int> ind{ 0,1,2 };
	std::vector<float> testt{ -1,-1, 0,1, 1,-1 };

	Shader shader;
	shader.AddShader(get_file_contents("base.vert").c_str(), GL_VERTEX_SHADER);
	shader.AddShader(get_file_contents("base.frag").c_str(), GL_FRAGMENT_SHADER);

	shader.Create();

	VAO vao;
	vao.init();
	vao.Bind();

	VBO vbo;
	EBO ebo;
	vbo.init(testt);
	ebo.init(ind);

	
	vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, sizeof(float) * 2, (void*)0);
	
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();

		vao.Bind();

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glClear(GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}
