#ifndef _lexical_cast_h__
#define _lexical_cast_h__

#include "glog.h"

namespace Study_Boost
{
	class boost_lexical_cast
	{
	public:
		static boost_lexical_cast* InitInstance();
		static void ExitInstance();
		static boost_lexical_cast* GetInstance();
	protected:
		static boost_lexical_cast* m_hInstance; 

	protected:
		boost_lexical_cast(){}
		~boost_lexical_cast(){}

	public:
		void runTest();

	private:
	};
}

#endif // _lexical_cast_h__
