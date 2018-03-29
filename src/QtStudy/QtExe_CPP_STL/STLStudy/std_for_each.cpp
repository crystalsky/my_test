#include "std_for_each.h"
#include "my_struct_def.h"
#include <xfunctional>
#include "boost\mpl\bind.hpp"

IMPLEMENT_REFLECTED_CLASS(std_for_each)
std_for_each::std_for_each()
{
	
}

std_for_each::~std_for_each()
{
	
}

struct my_for_each : public std::binary_function<my_struct, int, my_struct>
{
public:
	binary_function::result_type operator()(const my_struct& ms, int n)const
	{
		my_struct temp(ms);
		temp.nID *= n;
		return temp;
	}
};

void print(const my_struct& st)
{
	st.print();
}

struct printer
{
	void operator()(const my_struct& m)const
	{
		m.print();
	}
};

void std_for_each::run()
{
	ArrayStructs arrStructs;
	makeArray(arrStructs);

	std::for_each(arrStructs.begin(), 
		arrStructs.end(),
		std::bind2nd(my_for_each(), 2));


	//printer
	std::for_each(arrStructs.begin(), arrStructs.end(), print);

	std::for_each(arrStructs.begin(), arrStructs.end(), printer());

	std::for_each(arrStructs.begin(), arrStructs.end(), std::mem_fun_ref(&my_struct::print));




	ArrayDynamicStructs arrDynamicStructs;
	makeDynamicArray(arrDynamicStructs);
	std::for_each(arrDynamicStructs.begin(), 
		arrDynamicStructs.end(), std::mem_fun(&my_struct::print));
	std::for_each(arrDynamicStructs.begin(), arrDynamicStructs.end(), DeletePointer());
	arrDynamicStructs.clear();


	//
}
