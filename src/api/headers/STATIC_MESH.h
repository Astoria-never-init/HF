#ifndef API_STATIC_MESH_CLASS_H
#define API_STATIC_MESH_CLASS_H

class STATIC_MESH 
{
public:
	STATIC_MESH() {}

	bool add_LOD(float *positions, float *normals, float *texcoords, unsigned int size);

};

#endif