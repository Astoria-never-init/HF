#ifndef RENDER_VBO_CLASS_H
#define RENDER_VBO_CLASS_H

#include "BASE_BUFFER.h"
#include <vector>

class VBO : public BUFFER
{
public:
	void init(std::vector<float>& weights);
	void init(void * data, unsigned int size);

	void Bind() override;
	void Unbind() override;
	void Delete() override;
};
#endif