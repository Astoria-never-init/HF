#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "SHADER.h"
#include "TEXTURE.h"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "VIEWPORT_CAMERA.h"
#include <glm/gtc/type_ptr.hpp>

#include "RENDER_SECTION.h"
#include "SCENE_CULLING.h"

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
	glfwSwapInterval(1);
	gladLoadGL();
	glViewport(0, 0, X, Y);

	std::vector<unsigned int> ind{ 0,1,2 ,2, 1, 3};
	std::vector<float> testt{ -1, 0, -1,   0,0,    -1, 0, 1,   0,1,     1, 0, -1,   1,0,   1, 0, 1,   1,1 };

	RENDER_SECTION rs;
	rs.create(testt.data(), ind.data(), ind.size(), testt.size(), true, false);

	glm::vec3 bound_box[8]{
		glm::vec3(-1, 0, -1),
		glm::vec3(-1, 0, 1),
		glm::vec3(1, 0, -1),
		glm::vec3(1, 0, 1),
		glm::vec3(-1, 0, -1),
		glm::vec3(-1, 0, 1),
		glm::vec3(1, 0, -1),
		glm::vec3(1, 0, 1)
	};

	Shader shader;
	shader.AddShader(get_file_contents("res/base.vert").c_str(), GL_VERTEX_SHADER);
	shader.AddShader(get_file_contents("res/base.frag").c_str(), GL_FRAGMENT_SHADER);
	shader.Create();
	
	Shader shader_grid;
	shader_grid.AddShader(get_file_contents("res/grid.vert").c_str(), GL_VERTEX_SHADER);
	shader_grid.AddShader(get_file_contents("res/grid.frag").c_str(), GL_FRAGMENT_SHADER);
	shader_grid.Create();

	std::vector<unsigned int> xxi{ 0,1,2 ,3, 4, 5 };
	std::vector<float> xxv{
		1, 1, 0,
		-1, -1, 0, 
		-1, 1, 0, 
		-1, -1, 0, 
		1, 1, 0,
		1, -1, 0 };

	VAO vao;
	vao.init();
	vao.Bind();

	VBO vbo;
	EBO ebo;
	vbo.init(xxv);
	ebo.init(xxi);

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 3, (void*)0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	
	
	
	VIEWPORT_CAMERA camera(glm::vec3(0.0f, 0.0f, 0.0f), 75.0f, 0.1f, 100.0f, (float)X / Y);

	bool firstClick = true;

	int w, h, cnt;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("res/texture.jpg", &w, &h, &cnt, 0);
	
	float sensitivity = 100.0f;

	TEXTURE texture;
	texture.CreateTexture(data, w, h, cnt, 0);
	shader.setTexture2D("Test_Texture", texture.ID);

	

	glm::mat4 model(1.0f);
	model = glm::rotate (model, glm::radians(45.0f), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 6, 0));
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.move_forward(1);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.move_forward(-1);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.move_right(1);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.move_right(-1);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			camera.move_up(1);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			camera.move_up(-1);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			camera.speed = 0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			camera.speed = 0.02f;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			if (firstClick)
			{
				glfwSetCursorPos(window, (X / 2), (Y / 2));
				firstClick = false;
			}
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			camera.rotate(mouseX, mouseY, X, Y);

			glfwSetCursorPos(window, (X / 2), (Y / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}

		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		camera.Update();

		camera.GetCameraFrustream();
		shader.setMat4("Cam_Matrix", camera.Get_Matrix());
		shader.setMat4("Model_Matrix", model);

		shader_grid.setMat4("Cam_Matrix", camera.Get_Matrix());



		if (true || SCENE_CULLING::OOB_FrustreamCheck(camera, bound_box, model) )
		{
			shader.Activate();
			rs.draw();
		}
		
		
		shader_grid.Activate();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glClear(GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}
