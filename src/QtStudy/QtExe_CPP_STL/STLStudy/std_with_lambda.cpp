#include "std_with_lambda.h"
#include "my_struct_def.h"

IMPLEMENT_REFLECTED_CLASS(std_with_lambda)
std_with_lambda::std_with_lambda()
{
	
}

std_with_lambda::~std_with_lambda()
{
	
}

void test1(ArrayStructs& arr)
{
	std::for_each(arr.begin(), arr.end(), 
		[](const my_struct& s)
	{
		s.print();
	});
}

void test2(ArrayStructs& arr)
{
	ArrayStructs arr2;
	std::for_each(arr.begin(), arr.end(), 
		[&arr2](const my_struct& s)
	{
		arr2.push_back(s);
	});

	test1(arr2);
}

void test3(ArrayStructs& arr)
{
	ArrayStructs arr2;
	std::sort(arr.begin(), arr.end(), 
		[&arr2](const my_struct& s1, const my_struct& s2 )
	{
		return s1.nID < s2.nID;
	});

	test1(arr);
}

void std_with_lambda::run()
{
	ArrayStructs myVecData;

	makeArray(myVecData, 10, true);

	std::cout << "======lambda test1=======" << std::endl;
	test1(myVecData);
	
	std::cout << "======lambda test2=======" << std::endl;
	test2(myVecData);

	std::cout << "======lambda test3=======" << std::endl;
	test3(myVecData);
}
