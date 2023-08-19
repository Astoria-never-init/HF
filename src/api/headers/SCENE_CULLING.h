#ifndef API_SCENE_CULLING_CLASS_H
#define API_SCENE_CULLING_CLASS_H

#include "CAMERA.h"

class SCENE_CULLING
{
public:
	static bool POINT_FrustreamCheck(CAMERA & camera, glm::vec3 point, glm::mat4 ModelMatrix = glm::mat4(1.0f));//xyz - location, w - radius
	static bool SPHERE_FrustreamCheck(CAMERA & camera, glm::vec4 sphere, glm::mat4 ModelMatrix = glm::mat4(1.0f));//xyz - location, w - radius
	static bool OOB_FrustreamCheck(CAMERA & camera, glm::vec3 box[8], glm::mat4 ModelMatrix = glm::mat4(1.0f));//cube vertices
private:


};

#endif
