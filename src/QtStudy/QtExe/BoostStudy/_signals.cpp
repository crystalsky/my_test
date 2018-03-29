#include "_signals.h"

//#define BOOST_DISABLE_ASSERTS
//#define BOOST_ENABLE_ASSERT_HANDLER
#include "boost/assert.hpp"
#include "boost/static_assert.hpp"

#include "boost/signals2/signal.hpp"

#include "boost/format.hpp"
#include <iosfwd>
#include <iostream>
#include <boost/signals2/shared_connection_block.hpp>
#include <boost/bind.hpp>
namespace bs2 = boost::signals2;

//[ slot_arguments_slot_defs_code_snippet
void print_args(float x, float y)
{
	std::cout << "The arguments are " << x << " and " << y << std::endl;
}

void print_sum(float x, float y)
{
	std::cout << "The sum is " << x + y << std::endl;
}

void print_product(float x, float y)
{
	std::cout << "The product is " << x * y << std::endl;
}

void print_difference(float x, float y)
{
	std::cout << "The difference is " << x - y << std::endl;
}

void print_quotient(float x, float y)
{
	std::cout << "The quotient is " << x / y << std::endl;
}
//]

//[ signal_return_value_slot_defs_code_snippet
float product(float x, float y) { return x * y; }
float quotient(float x, float y) { return x / y; }
float sum(float x, float y) { return x + y; }
float difference(float x, float y) { return x - y; }
//]
struct HelloWorld
{
	void operator()()const
	{
		std::cout << "HelloWorld"; 
	}
};

namespace Study_Boost
{
	boost_signasl* boost_signasl::m_hInstance = NULL;
	
	boost_signasl* boost_signasl::InitInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_signasl;
		}
		return m_hInstance;
	}
	boost_signasl* boost_signasl::GetInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_signasl;
		}
		return m_hInstance;
	}
	
	void boost_signasl::ExitInstance()
	{
		if(m_hInstance)
		{
			delete m_hInstance;
			m_hInstance = NULL;
		}
	}

	void boost_signasl::runTest()
	{
		boost::format fmt("\n======================%s=====================");
		LOG(INFO) << fmt % "boost_signas";

		_test_HelloWorld();

		_test_hello_world_multi_slot();

		_test_ordering_slots();

		_test_slot_arguments();

		_test_signal_return_value();

		_test_custom_combiners();

		_test_disconnect();

		_test_block();

		_test_scoped_connection();

		_test_passing_slots();

		_test_doc_view();
	}

	void boost_signasl::_test_signal_return_value()
	{
		bs2::signal<float (float, float)> sig;

		sig.connect(&product);
		sig.connect(&quotient);
		sig.connect(&sum);
		sig.connect(&difference);

		std::cout << *sig(5., 3.);
	}

	void boost_signasl::_test_slot_arguments()
	{
		bs2::signal<void (float, float)> sig;

		sig.connect(&print_args);
		sig.connect(&print_sum);
		sig.connect(&print_product);
		sig.connect(&print_difference);
		sig.connect(&print_quotient);

		sig(5., 3.);
	}

	void boost_signasl::_test_HelloWorld()
	{
		bs2::signal<void()> sig;
		bs2::connection con = sig.connect(HelloWorld());
		sig();
	}

	void boost_signasl::_test_hello_world_multi_slot()
	{
		struct Hello
		{
			void operator()() const
			{
				std::cout << "Hello";
			}
		};

		struct World
		{
			void operator()() const
			{
				std::cout << ", World!" << std::endl;
			}
		};

		//[ good_morning_def_code_snippet
		struct GoodMorning
		{
			void operator()() const
			{
				std::cout << "... and good morning!" << std::endl;
			}
		};

		bs2::signal<void()> sig;
		bs2::connection con1 = sig.connect(Hello());
		bs2::connection con2 = sig.connect(World());
		bs2::connection con3 = sig.connect(GoodMorning());
		sig();
	}

	void boost_signasl::_test_ordering_slots()
	{
		struct Hello
		{
			void operator()() const
			{
				std::cout << "Hello";
			}
		};

		struct World
		{
			void operator()() const
			{
				std::cout << ", World!" << std::endl;
			}
		};

		//[ good_morning_def_code_snippet
		struct GoodMorning
		{
			void operator()() const
			{
				std::cout << "... and good morning!" << std::endl;
			}
		};
		
		//[ hello_world_ordered_code_snippet
		bs2::signal<void ()> sig;

		sig.connect(2, GoodMorning());
		sig.connect(1, World());  // connect with group 1
		sig.connect(0, Hello());  // connect with group 0

		sig();
	}


	template<typename Container>
	struct aggregate_values
	{
		typedef Container result_type;

		template<typename InputIterator>
		Container operator()(InputIterator first, InputIterator last) const
		{
			Container values;

			while(first != last) {
				values.push_back(*first);
				++first;
			}
			return values;
		}
	};

	template<typename T>
	struct maximum
	{
		typedef T result_type;

		template<typename InputIterator>
		T operator()(InputIterator first, InputIterator last) const
		{
			// If there are no slots to call, just return the
			// default-constructed value
			if(first == last ) return T();
			T max_value = *first++;
			while (first != last) {
				if (max_value < *first)
					max_value = *first;
				++first;
			}

			return max_value;
		}
	};

	void boost_signasl::_test_custom_combiners()
	{
		bs2::signal<float (float, float), aggregate_values<std::vector<float>>> sig;
		
		//[ custom_combiners_aggregate_values_usage_code_snippet
		sig.connect(&quotient);
		sig.connect(&product);
		sig.connect(&sum);
		sig.connect(&difference);

		std::vector<float> results = sig(5, 3);
		std::cout << "aggregate values: ";
		std::copy(results.begin(), results.end(),
			std::ostream_iterator<float>(std::cout, " "));
		std::cout << "\n";

		bs2::signal<float (float, float), maximum<float>> sigmax;
		sigmax.connect(&quotient);
		sigmax.connect(&product);
		sigmax.connect(&sum);
		sigmax.connect(&difference);
		float fMax = sigmax(5, 3);
		std::cout << "MaxValue = " << fMax << "\n";
	}

	void boost_signasl::_test_disconnect()
	{
		bs2::signal<void()> sig;
		bs2::connection con = sig.connect(HelloWorld());
		sig();

		con.disconnect();
		sig();
	}

	void boost_signasl::_test_block()
	{
		bs2::signal<void ()> sig;

		//[ block_code_snippet
		boost::signals2::connection c = sig.connect(HelloWorld());
		std::cout << "c is not blocked.\n";
		sig(); // Prints "Hello, World!"

		{
			bs2::shared_connection_block block(c); // block the slot
			std::cout << "c is blocked.\n";
			sig(); // No output: the slot is blocked
		} // shared_connection_block going out of scope unblocks the slot
		std::cout << "c is not blocked.\n";
		sig(); // Prints "Hello, World!"}
		//]
	}

	void boost_signasl::_test_scoped_connection()
	{
		struct ShortLived
		{
			void operator()() const
			{
				std::cout << "Life is short!" << std::endl;
			}
		};

		boost::signals2::signal<void ()> sig;

		//[ scoped_connection_code_snippet
		{
			boost::signals2::scoped_connection c(sig.connect(ShortLived()));
			sig(); // will call ShortLived function object
		} // scoped_connection goes out of scope and disconnects

		sig(); // ShortLived function object no longer connected to sig
		//]
	}

	class Button
	{
		typedef bs2::signal<void (int x, int y)> OnClick;
		typedef OnClick::slot_type OnClickSlotType;
	public:
		bs2::connection doOnClick(const OnClickSlotType& slot)
		{
			return click.connect(slot);
		}

		void simulateClick()
		{
			click(19, 24);
		}
	private:
		OnClick click;
	};

	void printCoordinates(int x, int y)
	{
		std::cout << "printCoordinates:(" << x << ", " << y << ")\n";
	}

	void boost_signasl::_test_passing_slots()
	{
		Button btn;
		btn.doOnClick(&printCoordinates);
		btn.simulateClick();
	}

	namespace DocumentView_1
	{
		namespace _t_1
		{
			class Document
			{
				typedef bs2::signal<void ()> signal_t;
				typedef signal_t::slot_type slot_t;
			public:
				Document(){}

				bs2::connection connect(const slot_t& subscriber)
				{
					return _sig.connect(subscriber);
				}

				void append(const char* s)
				{
					_strText += s;
					_sig();
				}

				std::string getText()const
				{
					return _strText;
				}
			private:
				signal_t _sig;
				std::string _strText;
			};

			class TextView
			{
			public:
				TextView(Document& doc): m_document(doc)
				{
					m_connection = m_document.connect(boost::bind(&TextView::refresh, this));
				}

				~TextView()
				{
					m_connection.disconnect();
				}

				void refresh()const
				{
					std::cout << "TextView: " << m_document.getText() << std::endl;
				}
			private:
				Document&        m_document;
				bs2::connection  m_connection;
			};


			class HexView
			{
			public:
				HexView(Document& doc): m_document(doc)
				{
					m_connection = m_document.connect(boost::bind(&HexView::refresh, this));
				}

				~HexView()
				{
					m_connection.disconnect();
				}

				void refresh()const
				{
					std::cout << "HexView:";

					const std::string s = m_document.getText();

					for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
						std::cout << ' ' << std::hex << static_cast<int>(*it);

					std::cout << std::endl;
				}

			private:
				Document&               m_document;
				bs2::connection  m_connection;
			};
		}
	}
	

	void boost_signasl::_test_doc_view()
	{
		DocumentView_1::_t_1::Document    doc;
		DocumentView_1::_t_1::TextView    v1(doc);
		DocumentView_1::_t_1::HexView     v2(doc);

		doc.append("_test_doc_view");

		/*DocumentView_1::_t_2::Document    doc2;
		DocumentView_1::_t_2::TextView    v1(doc2);
		DocumentView_1::_t_2::HexView     v2(doc2);

		doc.append("_test_doc_view");*/

	}

}