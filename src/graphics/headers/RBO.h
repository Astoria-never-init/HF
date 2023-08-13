#ifndef RENDER_RBO_CLASS_H
#define RENDER_RBO_CLASS_H

#include "BASE_BUFFER.h"

class RBO : public BUFFER
{
public:
	~RBO();

	void Create();
	void Bind() override;
	void Unbind() override;
	void Delete() override;
};

#endif