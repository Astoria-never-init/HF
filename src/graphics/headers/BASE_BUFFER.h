#ifndef RENDER_BUFFER_CLASS_H
#define RENDER_BUFFER_CLASS_H

class BUFFER
{
public:
	virtual  void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Delete() = 0;

	unsigned int getID();
protected:
	unsigned int ID;
};

#endif