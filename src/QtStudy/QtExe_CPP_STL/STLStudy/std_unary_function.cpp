#include "std_unary_function.h"
#include "inc_stl.h"
#include <xfunctional>

IMPLEMENT_REFLECTED_CLASS(std_unary_function)
std_unary_function::std_unary_function()
{
	
}

std_unary_function::~std_unary_function()
{
	
}


namespace test_resuable_design
{
	template<class T>
	class my_bind2nd : public std::unary_function<typename T::first_argument_type, typename T::result_type>
	{

	public:
		typedef typename T::second_argument_type second_value;

		my_bind2nd(T op1, second_value val)
		{
			this->op = op1;
			this->value = val;
		}

		result_type operator()(argument_type x)
		{
			return this->op(x, this->value);
		}

	private:
		T op;
		second_value  value;
	};

	template<class T>
	class my_Op
	{
	public:
		T operator()(const T& t1, const T& t2)
		{
			return std::pow(float(t1), float(t2)) / 3.0;
		}

		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
	};

	template<class T>
	class my_Op1 : public std::binary_function<T, T, T>
	{
	public:
		T operator()(const T& t1, const T& t2)
		{
			return std::pow(float(t1), float(t2)) / 3.0;
		}
	};

	template<class T, class V>
	inline my_bind2nd<T> bind2nd_2(T t, V val)
	{
		typedef typename T::second_argument_type sat;
		return my_bind2nd<T>(t, sat(val));
	}

	static void run()
	{
		int ar1[] = {1, 3, 5, 7, 9};
		std::vector<int> vec1(ar1, ar1 + sizeof(ar1) / sizeof(int));
		std::transform(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "), 
			bind2nd_2(std::plus<double>(), 2));
		std::cout << std::endl;

		std::transform(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "), 
			bind2nd_2(my_Op<double>(), 3));
		std::cout << std::endl;

		std::transform(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "), 
			bind2nd_2(my_Op1<double>(), 4));

		std::transform(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "),
			std::bind2nd(std::plus<double>(), 2));
	}
}

void std_unary_function::run()
{
	test_resuable_design::run();
}