#ifndef classoverride_h__
#define classoverride_h__

#include "Base.h"

class classoverride : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(classoverride)
public:
	classoverride();
	~classoverride();

public:
	virtual void run();
protected:
	
private:

};

#endif // classoverride_h__
