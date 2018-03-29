#include "my_struct_def.h"
#include <QString>

void makeArray(ArrayStructs& arry, int nCount, bool brand)
{
	arry.clear();

	if (nCount <= 0)
	{
		nCount = 100;
	}

	arry.reserve(nCount);

	for (int i = 0; i < nCount; ++i)
	{
		my_struct ms;
		if (brand)
		{
			ms.nID = qrand();
		}
		else
		{
			ms.nID = i + 1;
		}
		ms.strName = QString::fromLocal8Bit("Name:%1").arg(ms.nID).toLocal8Bit().data();
		arry.push_back(ms);
	}
}

void makeDynamicArray(ArrayDynamicStructs& arry, int nCount, bool brand)
{
	arry.clear();

	if (nCount <= 0)
	{
		nCount = 100;
	}

	arry.reserve(nCount);

	for (int i = 0; i < nCount; ++i)
	{
		my_struct *my = new my_struct;
		if (brand)
		{
			my->nID = qrand();
		}
		else
		{
			my->nID = i + 1;
		}
		my->strName = QString::fromLocal8Bit("Name:%1").arg(my->nID).toLocal8Bit().data();
		arry.push_back(my);
	}
}



extern void makeIntArray( std::vector<int>& arrInt, int nCount /*= 1000*/ )
{
	arrInt.clear();

	if (nCount <= 0)
	{
		nCount = 100;
	}

	arrInt.reserve(nCount);

	for (int i = 0; i < nCount; ++i)
	{
		arrInt.push_back(i);
	}
}
