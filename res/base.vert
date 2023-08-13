#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 textc;

uniform mat4 Cam_Matrix;
out vec2 UV;



void main()
{

	gl_Position = Cam_Matrix * vec4(pos, 0, 1.0) ;
	UV = textc;
}