#ifndef API_RENDER_SECTION_CLASS_H
#define API_RENDER_SECTION_CLASS_H

#include "glm/glm.hpp"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class RENDER_SECTION
{
public:
	RENDER_SECTION() {}

	bool create(float * verices, unsigned int * indices, unsigned int ind_count, unsigned int vert_count, bool include_texcoords, bool include_normals);
	void draw();
	glm::vec3* Get_bound_box() { return bound_box; }
	glm::vec4 Get_bound_sphere() { return bound_sphere; }
	
private:
	void CreateBounds(float * verices, unsigned int vert_count, unsigned short offset);

	unsigned int triangles_count = 0;

	glm::vec3 bound_box[8]; //simple box of object bounds
	glm::vec4 bound_sphere; //simple sphere of object bounds: xyz - center, w - radius

	VAO vao;
	VBO vbo;
	EBO ebo;
};

#endif