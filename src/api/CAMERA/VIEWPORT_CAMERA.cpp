#include "VIEWPORT_CAMERA.h"

VIEWPORT_CAMERA::VIEWPORT_CAMERA(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio)
{
	Init(position, FOVdeg, nearPlane, farPlane, aspectRatio);
}

void VIEWPORT_CAMERA::create(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio)
{
	Init(position, FOVdeg, nearPlane, farPlane, aspectRatio);
}

void VIEWPORT_CAMERA::move_forward(float val)
{
	AddLocation((val * speed) * Get_Orientation());
}

void VIEWPORT_CAMERA::move_right(float val)
{
	AddLocation((val * speed) * glm::normalize(glm::cross(Get_Orientation(), Up)));
}

void VIEWPORT_CAMERA::move_up(float val)
{
	AddLocation((val * speed) * Up);
}

void VIEWPORT_CAMERA::rotate(float x, float y, unsigned short window_size_x, unsigned short window_size_y)
{
	float rotYaw = sensitivity * (float)(y - (window_size_y / 2)) / window_size_y;
	float rotPitch = sensitivity * (float)(x - (window_size_x / 2)) / window_size_x;

	AddPitchRotation(-rotPitch);
	AddYawRotation(-rotYaw);
}
