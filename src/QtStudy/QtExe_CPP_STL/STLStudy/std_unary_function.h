#ifndef std_unary_function_h__
#define std_unary_function_h__

#include "Base.h"

class std_unary_function : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(std_unary_function)
public:
	std_unary_function();
	~std_unary_function();

public:
	virtual void run();

private:

};

#endif // std_unary_function_h__
