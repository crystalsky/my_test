#ifndef my_struct_def_h__
#define my_struct_def_h__

#include "inc_stl.h"

struct my_struct
{
	int nID;
	std::string strName;

	void print() const
	{ 
		std::cout 
			<< "my_struct::print: " 
			<< nID 
			<< ", Name:"
			<< strName.c_str()
			<< std::endl;
	}

	/*friend std::ostream& operator << (std::ostream& os, const my_struct& s)
	{
		os << s.nID << " " << s.strName;
		return os;
	}

	friend std::istream& operator >> (std::istream& is, my_struct& s)
	{
		is >> s.nID >> s.strName;
		return is;
	}*/
};

typedef std::vector<my_struct> ArrayStructs;
extern void makeArray(ArrayStructs& arry, int nCount = 100, bool brand = false);

typedef std::vector<my_struct*> ArrayDynamicStructs;
extern void makeDynamicArray(ArrayDynamicStructs& arry, int nCount = 100, bool brand = false);
struct DeletePointer
{
	template<typename T> void operator()( T* ptr ) const { delete ptr; }
};

typedef std::vector<int> ArrayInt;
extern void makeIntArray(std::vector<int>& arrInt, int nCount = 1000);

#endif // my_struct_def_h__
