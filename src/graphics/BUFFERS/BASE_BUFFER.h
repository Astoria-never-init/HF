#ifndef BUFFER_CLASS_H
#define BUFFER_CLASS_H

class BUFFER
{
public:
	virtual  void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Delete() = 0;

protected:
	unsigned int ID;
};

#endif