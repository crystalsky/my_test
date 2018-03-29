#include "_tuple.h"

//#define BOOST_DISABLE_ASSERTS
#define BOOST_ENABLE_ASSERT_HANDLER
#include "boost/assert.hpp"

#include "boost/static_assert.hpp"

namespace Study_Boost
{
	boost_tuple* boost_tuple::m_hInstance = NULL;
	
	boost_tuple* boost_tuple::InitInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_tuple;
		}
		return m_hInstance;
	}
	boost_tuple* boost_tuple::GetInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_tuple;
		}
		return m_hInstance;
	}
	
	void boost_tuple::ExitInstance()
	{
		if(m_hInstance)
		{
			delete m_hInstance;
			m_hInstance = NULL;
		}
	}

	void boost_tuple::runTest()
	{
		
	}
}