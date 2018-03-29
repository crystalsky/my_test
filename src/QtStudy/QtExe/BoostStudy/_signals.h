#ifndef _signals_h__
#define _signals_h__

#include "glog.h"

namespace Study_Boost
{
	class boost_signasl
	{
	public:
		static boost_signasl* InitInstance();
		static void ExitInstance();
		static boost_signasl* GetInstance();
	protected:
		static boost_signasl* m_hInstance; 

	protected:
		boost_signasl(){}
		~boost_signasl(){}

	public:
		void runTest();

	private:
		void _test_HelloWorld();
		void _test_hello_world_multi_slot();
		void _test_ordering_slots();
		void _test_slot_arguments();
		void _test_date_time();
		void _test_signal_return_value();
		void _test_custom_combiners();
		void _test_disconnect();
		void _test_block();
		void _test_scoped_connection();
		void _test_passing_slots();
		void _test_doc_view();

	};
}

#endif // _signals_h__
