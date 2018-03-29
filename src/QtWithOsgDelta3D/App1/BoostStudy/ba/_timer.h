#ifndef _timer_h__
#define _timer_h__

#include "glog.h"

namespace Study_Boost
{
	class boost_timer
	{
	public:
		static boost_timer* InitInstance();
		static void ExitInstance();
		static boost_timer* GetInstance();
	protected:
		static boost_timer* m_hInstance; 

	protected:
		boost_timer(){}
		~boost_timer(){}

	public:
		void runTest();

	private:
		void _test_Assert();
		void _test_timer();
		void _test_progress_time();
		void _test_date_time();
	};
}

#endif // _timer_h__
