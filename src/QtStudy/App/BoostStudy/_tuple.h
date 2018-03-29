#ifndef _tuple_h__
#define _tuple_h__

#include "glog.h"

namespace Study_Boost
{
	class boost_tuple
	{
	public:
		static boost_tuple* InitInstance();
		static void ExitInstance();
		static boost_tuple* GetInstance();
	protected:
		static boost_tuple* m_hInstance; 

	protected:
		boost_tuple(){}
		~boost_tuple(){}

	public:
		void runTest();

	private:
	};
}

#endif // _tuple_h__
