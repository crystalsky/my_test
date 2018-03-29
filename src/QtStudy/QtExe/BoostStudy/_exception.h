#ifndef _exception_h__
#define _exception_h__

#include "glog.h"
#include <iostream>
#include <boost/exception/all.hpp>

#define VR_EXCEPTION_TYPE_MESSAGE(exceptionType, message)\
	exceptionType(message, __FILE__, __LINE__)

#define VR_BASE_EXCEPTION(message)\
	VR_EXCEPTION_TYPE_MESSAGE(exception_base, message)

#define VR_THROW_EXCEPTION(exception_Type, nErrCode)\
	Study_Boost::throw_exception_ex( \
		exception_Type, \
		__FILE__, \
		BOOST_THROW_EXCEPTION_CURRENT_FUNCTION, \
		__LINE__, \
		nErrCode);

#define VR_THROW_EXCEPTION_REASON(exception_Type, nErrCode, errmsg)\
	Study_Boost::throw_exception_ex( \
	exception_Type, \
	__FILE__, \
	BOOST_THROW_EXCEPTION_CURRENT_FUNCTION, \
	__LINE__, \
	nErrCode, \
	errmsg);

#define DEFINE_ERROR_INFO(type, name) \
	typedef boost::error_info<struct tag_##name, type> name;

#define DEFINE_ERROR_INFO2(type, name) \
	typedef boost::error_info<struct tag_## __FILE__ ## __LINE__ ##name, type> name;
//#define EXCEPTION_WHAT_FORMAT_STRING
namespace Study_Boost
{
	DEFINE_ERROR_INFO(char const *, errorFunction);
	DEFINE_ERROR_INFO(char const *, errorFile);
	DEFINE_ERROR_INFO(char const *, errorReason);
	DEFINE_ERROR_INFO(int, errorLine);
	DEFINE_ERROR_INFO(int, errorCode);

	DEFINE_ERROR_INFO2(int, errorKK);

	class vire_exception : public std::exception, public virtual boost::exception
	{
	public:
		char const *
			what() const throw()
		{
			return "unknowen vire_exception...";
		}
	};

	template <typename T>
	static void throw_exception_ex(
		const T& t,
		const char* file, 
		const char* current_function, 
		int line,
		int nErrorCode = -9999,
		const char* errStr = NULL)
	{
		typedef typename boost::exception_detail::enable_error_info_return_type<T>::type _Exception_Result;

		_Exception_Result r = boost::enable_error_info(t)
			<< errorFunction(current_function)
			<< errorFile(file)
			<< errorLine(line);

		if (nErrorCode != -9999)
		{
			r << errorCode(nErrorCode);
		}
		if (errStr != NULL)
		{
			r << errorReason(errStr);
		}
		
		BOOST_THROW_EXCEPTION(r);
	}


	class exception_base : public std::exception
	{
	public:
		public:

         /**
          * Constructor - Initializes the exception and logs it.
          *  @param message - Message to display about the exception.
          *  @param filename - File the exception was thrown from.
          *  @param linenum - Line number in the file from which the
          *  exception was thrown.
          */
         explicit exception_base(const std::string& message, const std::string& filename, unsigned int linenum);

         /*
          * Destructor
          */
         virtual ~exception_base();

         const char * what() const;

         /*
          * @return the filename associated with this exception.
          */
         const std::string& File() const;

         /**
          * @return the line number associated with this exception.
          */
         unsigned int Line() const;

         /**
          * Converts this exception to a string.  The string contains the reason,
          * line number and file the exception was thrown from.
          * @return The string version of this exception.
          */
        virtual  std::string ToString() const;

         /**
          * Prints the exception to the console.
          */
         void Print() const;
      private:
         std::string mMessage, mFileName;
         unsigned int mLineNum;
		 std::string mFormatMessage;
	};

	class boost_exception
	{
	public:
		static boost_exception* InitInstance();
		static void ExitInstance();
		static boost_exception* GetInstance();
	protected:
		static boost_exception* m_hInstance; 

	protected:
		boost_exception(){}
		~boost_exception(){}

	public:
		void runTest();

	protected:
		void _test_error_info_1();
		void _test_error_info_2();
		void _test_io();
	};
}

namespace template_def
{
	

	template <class T, typename Container = std::vector<T>>
	class my_container
	{
	public:

		size_t size() const;

		T const &
			operator[]( size_t i ) const
		{
			if( i > size() )
				throw boost::enable_error_info(std::range_error("Index out of range")) <<
				std_range_min(0) <<
				std_range_max(size()) <<
				std_range_index(i);
		}

	private:
		Container mContainer;
	};

}

#endif // _exception_h__
