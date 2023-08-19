#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 textc;

uniform mat4 Cam_Matrix;
uniform mat4 Model_Matrix;
out vec2 UV;



void main()
{

	gl_Position = Cam_Matrix * Model_Matrix * vec4(pos, 1.0);
	UV = textc;
}