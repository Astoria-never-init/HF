#include"CAMERA.h"

//#include<glad/glad.h>
//#include<GLFW/glfw3.h>

#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <cstdlib>

void Camera::AddVectorRotate(glm::vec3 vec)
{
	Orientation = glm::normalize(Orientation * glm::normalize(vec));
}

void Camera::AddYawRotation(float angle_in_degree)
{
	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(angle_in_degree), glm::normalize(glm::cross(Orientation, Up)));

	if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Orientation = newOrientation;
	}
}

void Camera::AddPitchRotation(float angle_in_degree)
{
	Orientation = glm::rotate(Orientation, glm::radians(angle_in_degree), Up);
}

void Camera::AddLocation(glm::vec3 vec)
{
	Position += vec;
}

Camera::Camera(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio)
{
	Init(position, FOVdeg, nearPlane, farPlane, aspectRatio);
}

void Camera::Init(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio)
{
	Camera::Set_Position(position);
	Camera::Set_FOV(FOVdeg);
	Camera::Set_NearPlane(nearPlane);
	Camera::Set_FarPlane(farPlane);
	Camera::Set_AspectRatio(aspectRatio);
	Update_Projection();
}

void Camera::Update_Projection()
{
	Projection = glm::perspective(glm::radians(FOVdeg), aspectRatio, nearPlane, farPlane);
}

void Camera::Update()
{
	glm::mat4 view = glm::mat4(1.0f);
	
	view = glm::lookAt(Position, Position + Orientation, Up);

	Matrix = Projection * view;
}
