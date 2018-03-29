#include "_lexical_cast.h"
//#define BOOST_DISABLE_ASSERTS
//#define BOOST_ENABLE_ASSERT_HANDLER
#include "boost/assert.hpp"

#include "boost/static_assert.hpp"
#include "boost/lexical_cast.hpp"

namespace Study_Boost
{
	boost_lexical_cast* boost_lexical_cast::m_hInstance = NULL;
	
	boost_lexical_cast* boost_lexical_cast::InitInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_lexical_cast;
		}
		return m_hInstance;
	}
	boost_lexical_cast* boost_lexical_cast::GetInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_lexical_cast;
		}
		return m_hInstance;
	}
	
	void boost_lexical_cast::ExitInstance()
	{
		if(m_hInstance)
		{
			delete m_hInstance;
			m_hInstance = NULL;
		}
	}

	void t1()
	{
		int x = boost::lexical_cast<int>("100");
		long l = boost::lexical_cast<long>("2000");
		float pi = boost::lexical_cast<float>("3.1415926");
		double e = boost::lexical_cast<double>("23215413423423424e-10");
	}

	template<typename T>
	bool Convert(const std::string& srV, T& val)
	{
		try
		{
			val = boost::lexical_cast<T>(srV);
		}
		catch(boost::bad_lexical_cast& e)
		{
			LOG(ERROR) << e.what();
			return false;
		}
		return true;
	}

	void boost_lexical_cast::runTest()
	{
		t1();

		int v = 0;
		Convert("1.234", v);

		Convert("1.234v", v);
	}
}