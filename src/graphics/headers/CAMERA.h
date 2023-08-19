#ifndef RENDER_CAMERA_CLASS_H
#define RENDER_CAMERA_CLASS_H

#include<glm/glm.hpp>

class CAMERA
{
public:

	void Set_FOV(float val) { FOVdeg = val; }
	void Set_NearPlane(float val) { nearPlane = val; }
	void Set_FarPlane(float val) { farPlane = val; }
	void Set_AspectRatio(float val) { aspectRatio = val; }
	void Set_Position(glm::vec3 vec) { Position = vec; }

	float Get_FOV() { return FOVdeg; }
	float Get_NearPlane() { return nearPlane; }
	float Get_FarPlane() { return farPlane; }
	float Get_AspectRatio() { return aspectRatio; }
	glm::vec3 Get_Position() { return Position; }
	glm::vec3 Get_Orientation() { return Orientation; }
	glm::mat4 Get_Matrix() { return Matrix; }
	glm::vec4 * GetCameraFrustream() { return Frustream; }

	void AddVectorRotate(glm::vec3 vec);
	void AddYawRotation(float angle_in_degree);
	void AddPitchRotation(float angle_in_degree);
	void AddLocation(glm::vec3 vec);
	

	CAMERA() {};
	CAMERA(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio);
	void Init(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, float aspectRatio);

	void Update();
	void Update_Projection();

	
	
	
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	
protected:
	void UpdateCameraFrustream();

	glm::vec4 Frustream[6];
	glm::mat4 Matrix;
	glm::mat4 Projection;
	float FOVdeg, nearPlane, farPlane, aspectRatio;
	glm::vec3 Position;
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif