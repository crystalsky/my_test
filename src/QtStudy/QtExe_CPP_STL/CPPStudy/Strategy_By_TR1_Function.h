#ifndef Strategy_By_TR1_Function_h__
#define Strategy_By_TR1_Function_h__

#include "Base.h"

class Strategy_By_TR1_Function : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(Strategy_By_TR1_Function)
public:
	Strategy_By_TR1_Function();
	~Strategy_By_TR1_Function();

public:
	virtual void run();
protected:
	
private:

};

#endif // Strategy_By_TR1_Function_h__
