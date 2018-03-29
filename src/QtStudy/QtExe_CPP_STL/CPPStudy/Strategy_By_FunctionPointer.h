#ifndef Strategy_By_FunctionPointer_h__
#define Strategy_By_FunctionPointer_h__

#include "Base.h"

class Strategy_By_FunctionPointer : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(Strategy_By_FunctionPointer)
public:
	Strategy_By_FunctionPointer();
	~Strategy_By_FunctionPointer();

public:
	virtual void run();
protected:
	
private:

};

#endif // Strategy_By_FunctionPointer_h__
