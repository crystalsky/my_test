#ifndef Non_Virtual_Interface_h__
#define Non_Virtual_Interface_h__

#include "Base.h"

class Non_Virtual_Interface : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(Non_Virtual_Interface)
public:
	Non_Virtual_Interface();
	~Non_Virtual_Interface();

public:
	virtual void run();
protected:
	
private:

};

#endif // Non_Virtual_Interface_h__
