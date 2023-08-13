#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "SHADER.h"
#include "CAMERA.h"
#include "TEXTURE.h"
#include <fstream>
#include "test.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



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
	std::vector<float> testt{ -1,-1, 0,0,    -1,1, 0,1,     1,-1, 1,0,   1,1, 1,1 };

	Shader shader;
	shader.AddShader(get_file_contents("res/base.vert").c_str(), GL_VERTEX_SHADER);
	shader.AddShader(get_file_contents("res/base.frag").c_str(), GL_FRAGMENT_SHADER);

	shader.Create();
	


	VAO vao;
	vao.init();
	vao.Bind();

	VBO vbo;
	EBO ebo;
	vbo.init(testt);
	ebo.init(ind);

	
	vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, sizeof(float) * 4, (void*)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	
	Camera camera(glm::vec3(0.0f, -1.0f, 0.0f), 75.0f, 0.1f, 100.0f, (float)X / Y);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Position = glm::vec3(0,0,0);
	float speed = 0.02f;
	float sensitivity = 100.0f;
	bool firstClick = true;

	int w, h, cnt;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("res/texture.jpg", &w, &h, &cnt, 0);
	
	

	TEXTURE texture;
	texture.CreateTexture(data, w, h, cnt, 0);
	shader.setTexture2D("Test_Texture", texture.ID);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Position += speed * camera.Get_Orientation();
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Position += speed * -glm::normalize(glm::cross(camera.Get_Orientation(), Up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Position += speed * -camera.Get_Orientation();
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Position += speed * glm::normalize(glm::cross(camera.Get_Orientation(), Up));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			Position += speed * Up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			Position += speed * -Up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			speed = 0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			speed = 0.02f;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			// Hides mouse cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				glfwSetCursorPos(window, (X / 2), (Y / 2));
				firstClick = false;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotYaw = sensitivity * (float)(mouseY - (Y / 2)) / Y;
			float rotPitch = sensitivity * (float)(mouseX - (X / 2)) / X;


			camera.AddPitchRotation(-rotPitch);
			camera.AddYawRotation(-rotYaw);

			glfwSetCursorPos(window, (X / 2), (Y / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}

		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		camera.Set_Position(Position);
		camera.Update();

		
		shader.setMat4("Cam_Matrix", camera.Get_Matrix());

		shader.Activate();

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
