#ifndef template_test_1_h__
#define template_test_1_h__

#include "Base.h"

class template_test_1 : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(template_test_1)
public:
	template_test_1();
	~template_test_1();

public:
	virtual void run();
protected:
	void test_MyContainer();

	void test_RealContainer();

	void test_serialize_container();

private:

};

#endif // template_test_1_h__
