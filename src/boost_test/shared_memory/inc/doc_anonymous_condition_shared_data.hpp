//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <boost/interprocess/detail/config_begin.hpp>
//[doc_anonymous_condition_shared_data
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

#define _KB 1024
#define _MB (_KB * _KB)
#define _GB (_KB * _MB)

//#define USE_WINDOW

class trace_queue
{
private:
	char*	m_dstDatas;
	long long		m_nBufferSize;
public:
	enum { LineSize = 50, RowSize = 10 * _MB};
	trace_queue()
		: message_in(false)
		, m_nBufferSize(LineSize * RowSize)
		, m_nDataIndex(0)
	{

	}

	~trace_queue()
	{
		
	}

	//Mutex to protect access to the queue
	boost::interprocess::interprocess_mutex      mutex;

	//Condition to wait when the queue is empty
	boost::interprocess::interprocess_condition  cond_empty;

	//Condition to wait when the queue is full
	boost::interprocess::interprocess_condition  cond_full;

	static long long getBufferSize(){return LineSize * RowSize;}

	//Items to fill
	char   items[LineSize];

	//unsigned char   *m_itemsaddr[LineSize];
	//char**	m_pItems;
	int m_nDataIndex;

	//Is there any message
	bool message_in;

};
//]
#include <boost/interprocess/detail/config_end.hpp>
