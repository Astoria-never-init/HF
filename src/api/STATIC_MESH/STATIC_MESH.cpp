#include "..\headers\STATIC_MESH.h"

bool STATIC_MESH::add_LOD(float * positions, float * normals, float * texcoords, unsigned int size)
{
	if ((!positions) || (!normals) || (!texcoords))
	{
		return false;
	}
}
