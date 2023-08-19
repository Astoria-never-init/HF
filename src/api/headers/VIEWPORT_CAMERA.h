#ifndef API_VIEWPORT_CAMERA_CLASS_H
#define API_VIEWPORT_CAMERA_CLASS_H

#include "CAMERA.h"

class VIEWPORT_CAMERA : public CAMERA
{
public:
	VIEWPORT_CAMERA() {}
	VIEWPORT_CAMERA(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio);
	void create(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio);
	void move_forward(float val);
	void move_right(float val);
	void move_up(float val);
	void rotate(float x, float y, unsigned short window_size_x, unsigned short window_size_y);

	float speed = 0.02f;
	float sensitivity = 100.0f;
private:
	

};

#endif
