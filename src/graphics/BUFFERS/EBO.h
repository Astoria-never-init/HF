#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "BASE_BUFFER.h"
#include <vector>

class EBO : public BUFFER
{
public:
	~EBO();

	void init(std::vector<unsigned int>& indices);
	void init(void * data, unsigned int size);

	void Bind() override;
	void Unbind() override;
	void Delete() override;
};

#endif
