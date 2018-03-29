#include "_circle_buffer.h"
#include <boost/circular_buffer.hpp>
#include <boost/iterator.hpp>
#include <iterator>
#include <numeric>
#include <vector>
#include <boost/circular_buffer.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <boost/call_traits.hpp>
#include <boost/bind.hpp>

#include <boost/timer/timer.hpp> // for auto_cpu_timer
#if !defined(BOOST_NO_EXCEPTIONS)
#include <exception>
#endif

IMPLEMENT_REFLECTED_CLASS(_circle_buffer)
_circle_buffer::_circle_buffer()
{
	
}

_circle_buffer::~_circle_buffer()
{
	
}



template <class T>
class bounded_buffer
{
public:
	typedef boost::circular_buffer<T> container_type;
	typedef typename container_type::size_type size_type;
	typedef typename container_type::value_type value_type;
	typedef typename boost::call_traits<value_type>::param_type param_type;

	explicit bounded_buffer(size_type capacity) : m_unread(0), m_container(capacity) {}
	
	void push_front(const param_type* arrItem, int nSize)
	{ // `param_type` represents the "best" way to pass a parameter of type `value_type` to a method.
		if (arrItem == NULL ||
			nSize <= 0)
		{
			return;
		}

		boost::mutex::scoped_lock lock(m_mutex);
		m_not_full.wait(lock, boost::bind(&bounded_buffer<value_type>::is_not_full, this));
		
		m_vecBufferSize.push_front(nSize);
		for (int i = 0; i < nSize; ++i)
		{
			const param_type& item = arrItem[i];
			m_container.push_front(item);
			++m_unread;
		}
		
		lock.unlock();
		m_not_empty.notify_one();
	}

	void pop_back(value_type** pItem, int &nSize) {
		boost::mutex::scoped_lock lock(m_mutex);
		m_not_empty.wait(lock, boost::bind(&bounded_buffer<value_type>::is_not_empty, this));
		
		int nBufferSize = m_vecBufferSize.pop_back();
		*pItem = new value_type[nBufferSize];
		for (int i = 0; i < nBufferSize; ++i)
		{
			*pItem + i = m_container[--m_unread];
		}
		
		lock.unlock();
		m_not_full.notify_one();
	}

	void push_front(typename boost::call_traits<value_type>::param_type item)
	{ // `param_type` represents the "best" way to pass a parameter of type `value_type` to a method.

		boost::mutex::scoped_lock lock(m_mutex);
		m_not_full.wait(lock, boost::bind(&bounded_buffer<value_type>::is_not_full, this));
		m_container.push_front(item);
		++m_unread;
		lock.unlock();
		m_not_empty.notify_one();
	}

	void pop_back(value_type* pItem, int nSize) {
		boost::mutex::scoped_lock lock(m_mutex);
		m_not_empty.wait(lock, boost::bind(&bounded_buffer<value_type>::is_not_empty, this));
		*pItem = m_container[--m_unread];
		lock.unlock();
		m_not_full.notify_one();
	}

private:
	bounded_buffer(const bounded_buffer&);              // Disabled copy constructor.
	bounded_buffer& operator = (const bounded_buffer&); // Disabled assign operator.

	bool is_not_empty() const { return m_unread > 0; }
	bool is_not_full() const { return m_unread < m_container.capacity(); }

	size_type m_unread;
	container_type m_container;
	
	boost::circular_buffer<int>	m_vecBufferSize;
	boost::mutex m_mutex;
	boost::condition m_not_empty;
	boost::condition m_not_full;
};

boost::shared_ptr<bounded_buffer<char>> g_buffer;
#define  B_SIZE (1000 * 1024)
void _circle_buffer::run()
{
	g_buffer.reset(new bounded_buffer<char>(B_SIZE));

	
	// Create a circular buffer with a capacity for 3 integers.
	/*boost::circular_buffer<int> cb(3);
	
	// Insert threee elements into the buffer.
	cb.push_back(1);
	cb.push_back(2);
	cb.push_back(3);

	int a = cb[0];  // a == 1
	int b = cb[1];  // b == 2
	int c = cb[2];  // c == 3

	// The buffer is full now, so pushing subsequent
	// elements will overwrite the front-most elements.

	cb.push_back(4);  // Overwrite 1 with 4.
	cb.push_back(5);  // Overwrite 2 with 5.

	// The buffer now contains 3, 4 and 5.
	a = cb[0];  // a == 3
	b = cb[1];  // b == 4
	c = cb[2];  // c == 5

	// Elements can be popped from either the front or the back.
	cb.pop_back();  // 5 is removed.
	cb.pop_front(); // 3 is removed.

	// Leaving only one element with value = 4.
	int d = cb[0];  // d == 4*/
}
