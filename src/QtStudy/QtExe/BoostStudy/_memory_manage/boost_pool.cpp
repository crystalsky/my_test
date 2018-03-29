#include "boost_pool.h"

#include <list>
#include "QList"

boost::pool<> boost_pool::pdouble(sizeof(double));

IMPLEMENT_REFLECTED_CLASS(boost_pool)
boost_pool::boost_pool() 
{
	
}

boost_pool::~boost_pool()
{
	
}

void boost_pool::run()
{
	for (int i = 0; i < 10; ++i)
	{
		my o;
		//o.mallocobj();
		o.nRowCount = 1024;
		o.nColumeCount = 1024;
		o.m_pValue = (double*)pdouble.ordered_malloc(o.nRowCount * o.nColumeCount);
		o.m_pLatLong = (double*)pdouble.ordered_malloc(o.nRowCount * o.nColumeCount * 2);

		mListMy << o;
	}

	for (int i = 0; i < 10; ++i)
	{
		my o = mListMy.takeFirst();

		pdouble.free(o.m_pValue);
		pdouble.free(o.m_pLatLong);
	}

}
