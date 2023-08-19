#include "..\headers\RENDER_SECTION.h"
#include<glad/glad.h>
#include<iostream>

bool RENDER_SECTION::create(float * verices, unsigned int * indices, unsigned int ind_count, unsigned int vert_count, bool include_texcoords, bool include_normals)
{
	if (!verices) return false;

	unsigned short summ = 3 + (include_texcoords ? 2 : 0) + (include_normals ? 3 : 0);
	vao.init();
	vao.Bind();

	vbo.init(verices, vert_count * sizeof(float));
	ebo.init(indices, ind_count * sizeof(unsigned int));

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * summ, (void*)0);
	if (include_texcoords && include_normals)
	{
		vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(float) * summ, (void*)(sizeof(float) * 3));
		vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(float) * summ, (void*)(sizeof(float) * 5));
	}
	else if(include_texcoords)
	{
		vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(float) * summ, (void*)(sizeof(float) * 3));
	}
	else if (include_normals)
	{
		vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(float) * summ, (void*)(sizeof(float) * 3));
	}

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	

	CreateBounds(verices, vert_count, summ);
	
	triangles_count = ind_count;
	
}

void RENDER_SECTION::draw()
{
	vao.Bind();
	glDrawElements(GL_TRIANGLES, triangles_count, GL_UNSIGNED_INT, 0);
}

void RENDER_SECTION::CreateBounds(float * verices, unsigned int vert_count, unsigned short offset)
{
	glm::vec3 bb_min(0.0f);
	glm::vec3 bb_max(0.0f);
	for (unsigned int i = 0; i < vert_count; i += offset)
	{
		bb_min.x = (bb_min.x < verices[i]) ? bb_min.x : verices[i];
		bb_min.y = (bb_min.y < verices[i + 1]) ? bb_min.y : verices[i + 1];
		bb_min.z = (bb_min.z < verices[i + 2]) ? bb_min.z : verices[i + 2];

		bb_max.x = (bb_max.x > verices[i]) ? bb_max.x : verices[i];
		bb_max.y = (bb_max.y > verices[i + 1]) ? bb_max.y : verices[i + 1];
		bb_max.z = (bb_max.z > verices[i + 2]) ? bb_max.z : verices[i + 2];
	}
	bound_box[0] = bb_min;
	bound_box[1] = glm::vec3(bb_max.x, bb_min.y, bb_min.z);
	bound_box[2] = glm::vec3(bb_min.x, bb_max.y, bb_min.z);
	bound_box[3] = glm::vec3(bb_min.x, bb_min.y, bb_max.z);
	bound_box[4] = glm::vec3(bb_max.x, bb_max.y, bb_min.z);
	bound_box[5] = glm::vec3(bb_min.x, bb_max.y, bb_max.z);
	bound_box[6] = glm::vec3(bb_max.x, bb_min.y, bb_max.z);
	bound_box[7] = bb_max;

	glm::vec3 center = ((bb_min + bb_max) / 2.0f);
	bound_sphere = glm::vec4(center, glm::distance(center, bb_max));
}
