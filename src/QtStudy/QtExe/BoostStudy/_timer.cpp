#include "_timer.h"
#include "boost/timer.hpp"
#include "boost/progress.hpp"

//#define BOOST_DISABLE_ASSERTS
#define BOOST_ENABLE_ASSERT_HANDLER
#include "boost/assert.hpp"

#include "boost/static_assert.hpp"

#include "boost/date_time/gregorian/greg_date.hpp"

#include "boost/format.hpp"
#include <iosfwd>

namespace boost
{
	void assertion_failed(char const * expr,
		char const * function, char const * file, long line)
	{
		boost::format fmt("Assertion Failed!\n Expression: %s\nFunction:%s\nFile:%s\nLine: %ld\n\n");
		fmt % expr % function % file % line;
		LOG(ERROR) << fmt;
	}
}

namespace Study_Boost
{
	boost_timer* boost_timer::m_hInstance = NULL;
	
	boost_timer* boost_timer::InitInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_timer;
		}
		return m_hInstance;
	}
	boost_timer* boost_timer::GetInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_timer;
		}
		return m_hInstance;
	}
	
	void boost_timer::ExitInstance()
	{
		if(m_hInstance)
		{
			delete m_hInstance;
			m_hInstance = NULL;
		}
	}

	void boost_timer::runTest()
	{
		_test_Assert();
		
		_test_timer();

		_test_progress_time();

		_test_date_time();
	}

	template<typename T>
	T my_min(T t1, T t2)
	{
		BOOST_STATIC_ASSERT(sizeof(T) < sizeof(int));
		return t1 < t2 ? t1 : t2;
	}
	class A
	{
	public:
		A(){}
	};
	void boost_timer::_test_Assert()
	{
		BOOST_ASSERT(16 == 0x10);
		BOOST_ASSERT(16 != 0x10 && "Not Equal Failed!");

		int a = sizeof(A);

		//
		//BOOST_STATIC_ASSERT(3 == sizeof(short));
		BOOST_STATIC_ASSERT(2 == sizeof(short));

		//my_min(5L, 6L);
		my_min((short)5, (short)6);
	}

	void boost_timer::_test_timer()
	{
		boost::timer t;

		LOG(INFO) << "boost::timer max timespan: "	<< t.elapsed_max();
		LOG(INFO) << "boost::timer min TimeSpan: "	<< t.elapsed_min();

		LOG(INFO) << "boost::timer now Time Elapsed: " << t.elapsed();
	}

	void boost_timer::_test_progress_time()
	{
		{
			std::stringstream os;
			{
				boost::progress_timer t2(os);
				for (int i = 0; i < 100; ++i)
				{
					for (int i = 0; i < 100000; ++i)
					{

					}
				}

			}
			LOG(INFO) << "boost::progress_timer " << os.str();
		}

		
	}

	void boost_timer::_test_date_time()
	{
		boost::gregorian::date d1;
		boost::gregorian::date d2(2014, 10, 14);
		boost::gregorian::date d3(d2);

		BOOST_ASSERT(d1 != boost::gregorian::date(boost::gregorian::not_a_date_time));
		BOOST_ASSERT(d1 == boost::gregorian::date(boost::gregorian::not_a_date_time));
		BOOST_ASSERT(d2 == d3);

		
	}
}