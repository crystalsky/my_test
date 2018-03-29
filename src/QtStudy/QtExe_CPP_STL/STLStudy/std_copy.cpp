#include "std_copy.h"
#include "my_struct_def.h"
#include <iterator>
#include <TTimePrint.h>
#include<iostream>
#include<vector>
#include<time.h>
#include<iosfwd>
#include<algorithm>
#include<stdio.h>

using namespace std;

IMPLEMENT_REFLECTED_CLASS(std_copy)
std_copy::std_copy()
{
	
}

std_copy::~std_copy()
{
	
}

void std_copy::run()
{
	const int nNum = 1500000;
	{//拷贝到空数组处理
		ArrayInt arr1, arr2, arr3;
		makeIntArray(arr1, nNum);

		//std::copy(arr1.begin(), arr1.end(), arr2.begin());//崩溃，需要升请内存先
		TTRestart;
		std::copy(arr1.begin(), arr1.end(), std::back_inserter(arr2));

		TTPrintAndRestart("1 copy")
		
		arr3.resize(nNum);
		std::copy(arr1.begin(), arr1.end(), arr3.begin());
		TTPrint("2 copy");
	}
	
	{//拷贝效率
		ArrayInt arr1;
		makeIntArray(arr1, nNum);

		int *pInt = new int[nNum];

		TTRestart;
		std::copy(arr1.begin(), arr1.end(), pInt);
		TTPrintAndRestart("use copy");

		for (int i = 0; i < nNum; ++i)
		{
			pInt[i] = arr1[i];
		}
		TTPrintAndRestart("use for");

		int *p = pInt;
		for (int i = 0; i < nNum; ++i)
		{
			*p++ = arr1[i];
		}
		TTPrintAndRestart("use for ptr");

		delete []pInt;
	}
}
