#include "SCENE_CULLING.h"

bool SCENE_CULLING::POINT_FrustreamCheck(CAMERA & camera, glm::vec3 point, glm::mat4 ModelMatrix)
{
	glm::vec4 * frustream = camera.GetCameraFrustream();
	for (int i = 0; i < 6; i++)
	{
		if (frustream[i].x * point.x + frustream[i].y * point.y + frustream[i].z * point.z + frustream[i].w <= 0)
		{
			return false;
		}
	}
	return true;
}

bool SCENE_CULLING::SPHERE_FrustreamCheck(CAMERA & camera, glm::vec4 sphere, glm::mat4 ModelMatrix)
{
	glm::vec3 sp = glm::vec3(sphere * ModelMatrix);
	glm::vec4 * frustream = camera.GetCameraFrustream();
	for (int i = 0; i < 6; i++)
	{
		if (frustream[i].x * sp.x + frustream[i].y * sp.y + frustream[i].z * sp.z + frustream[i].w <= -sphere.w)
		{
			return false;
		}
	}
	return true;
}

bool SCENE_CULLING::OOB_FrustreamCheck(CAMERA & camera, glm::vec3 box[8], glm::mat4 ModelMatrix)
{
	glm::vec4 obb_points[8];
	for (int i = 0; i < 8; i++)
	{
		obb_points[i] = camera.Get_Matrix() * ModelMatrix * glm::vec4(box[i], 1);
	}
	bool outside = false, outside_positive_plane, outside_negative_plane;
	for (int i = 0; i < 3; i++)
	{
		outside_positive_plane =
			obb_points[0][i] > obb_points[0].w &&
			obb_points[1][i] > obb_points[1].w &&
			obb_points[2][i] > obb_points[2].w &&
			obb_points[3][i] > obb_points[3].w &&
			obb_points[4][i] > obb_points[4].w &&
			obb_points[5][i] > obb_points[5].w &&
			obb_points[6][i] > obb_points[6].w &&
			obb_points[7][i] > obb_points[7].w;
	
		outside_negative_plane =
			obb_points[0][i] < -obb_points[0].w &&
			obb_points[1][i] < -obb_points[1].w &&
			obb_points[2][i] < -obb_points[2].w &&
			obb_points[3][i] < -obb_points[3].w &&
			obb_points[4][i] < -obb_points[4].w &&
			obb_points[5][i] < -obb_points[5].w &&
			obb_points[6][i] < -obb_points[6].w &&
			obb_points[7][i] < -obb_points[7].w;
	
		outside = outside || outside_positive_plane || outside_negative_plane;
	}
	return !outside;
}
