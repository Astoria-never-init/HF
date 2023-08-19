#include"CAMERA.h"

//#include<glad/glad.h>
//#include<GLFW/glfw3.h>

#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <cstdlib>

void CAMERA::AddVectorRotate(glm::vec3 vec)
{
	Orientation = glm::normalize(Orientation * glm::normalize(vec));
}

void CAMERA::AddYawRotation(float angle_in_degree)
{
	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(angle_in_degree), glm::normalize(glm::cross(Orientation, Up)));

	if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Orientation = newOrientation;
	}
}

void CAMERA::AddPitchRotation(float angle_in_degree)
{
	Orientation = glm::rotate(Orientation, glm::radians(angle_in_degree), Up);
}

void CAMERA::AddLocation(glm::vec3 vec)
{
	Position += vec;
}

CAMERA::CAMERA(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio)
{
	Init(position, FOVdeg, nearPlane, farPlane, aspectRatio);
}

void CAMERA::Init(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio)
{
	CAMERA::Set_Position(position);
	CAMERA::Set_FOV(FOVdeg);
	CAMERA::Set_NearPlane(nearPlane);
	CAMERA::Set_FarPlane(farPlane);
	CAMERA::Set_AspectRatio(aspectRatio);
	Update_Projection();
}

void CAMERA::Update_Projection()
{
	Projection = glm::perspective(glm::radians(FOVdeg), aspectRatio, nearPlane, farPlane);
}

void CAMERA::UpdateCameraFrustream()
{
	Frustream[0].x = Matrix[0][3] - Matrix[0][0];
	Frustream[0].y = Matrix[1][3] - Matrix[1][0];
	Frustream[0].z = Matrix[2][3] - Matrix[2][0];
	Frustream[0].w = Matrix[3][3] - Matrix[3][0];
	Frustream[0] /= glm::length(glm::vec3(Frustream[0]));


	Frustream[1].x = Matrix[0][3] + Matrix[0][0];
	Frustream[1].y = Matrix[1][3] + Matrix[1][0];
	Frustream[1].z = Matrix[2][3] + Matrix[2][0];
	Frustream[1].w = Matrix[3][3] + Matrix[3][0];
	Frustream[1] /= glm::length(glm::vec3(Frustream[1]));


	Frustream[2].x = Matrix[0][3] + Matrix[0][1];
	Frustream[2].y = Matrix[1][3] + Matrix[1][1];
	Frustream[2].z = Matrix[2][3] + Matrix[2][1];
	Frustream[2].w = Matrix[3][3] + Matrix[3][1];
	Frustream[2] /= glm::length(glm::vec3(Frustream[2]));

	Frustream[3].x = Matrix[0][3] - Matrix[0][1];
	Frustream[3].y = Matrix[1][3] - Matrix[1][1];
	Frustream[3].z = Matrix[2][3] - Matrix[2][1];
	Frustream[3].w = Matrix[3][3] - Matrix[3][1];
	Frustream[3] /= glm::length(glm::vec3(Frustream[3]));


	Frustream[4].x = Matrix[0][3] - Matrix[0][2];
	Frustream[4].y = Matrix[1][3] - Matrix[1][2];
	Frustream[4].z = Matrix[2][3] - Matrix[2][2];
	Frustream[4].w = Matrix[3][3] - Matrix[3][2];
	Frustream[4] /= glm::length(glm::vec3(Frustream[4]));


	Frustream[5].x = Matrix[0][3] + Matrix[0][2];
	Frustream[5].y = Matrix[1][3] + Matrix[1][2];
	Frustream[5].z = Matrix[2][3] + Matrix[2][2];
	Frustream[5].w = Matrix[3][3] + Matrix[3][2];
	Frustream[5] /= glm::length(glm::vec3(Frustream[5]));
}

void CAMERA::Update()
{
	glm::mat4 view = glm::mat4(1.0f);
	
	view = glm::lookAt(Position, Position + Orientation, Up);

	Matrix = Projection * view;

	UpdateCameraFrustream();
}
