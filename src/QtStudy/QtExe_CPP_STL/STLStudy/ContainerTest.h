#ifndef ContainerTest_h__
#define ContainerTest_h__

#include "Base.h"

class ContainerTest : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(ContainerTest)
public:
	ContainerTest();
	~ContainerTest();

public:
	virtual void run();
protected:
	void _comapare_list_2_vector();

	void _compare_vector();

	void _938_find_char();

	void _939_word_count();

	void _stack();

	void _vector_test();
private:

};

#endif // ContainerTest_h__
