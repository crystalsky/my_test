#ifndef _circle_buffer_h__
#define _circle_buffer_h__

#include "Base.h"

class _circle_buffer : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(_circle_buffer)
public:
	_circle_buffer();
	~_circle_buffer();

public:
	virtual void run();
protected:
	
private:

};

#endif // _circle_buffer_h__
