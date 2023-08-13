#ifndef RENDER_FBO_CLASS_H
#define RENDER_FBO_CLASS_H

#include "BASE_BUFFER.h"

class FBO : public BUFFER
{
public:
	~FBO();

	void init();

	void Bind() override;
	void Unbind() override;
	void Delete() override;
};

#endif