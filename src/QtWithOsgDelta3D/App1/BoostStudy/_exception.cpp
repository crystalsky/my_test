#include "_exception.h"
#include "boost\throw_exception.hpp"
#include "boost\exception\errinfo_file_handle.hpp"

namespace Study_Boost
{
	//////////////////////////////////////////////////////////////////////////
	exception_base::exception_base(
		const std::string& message, 
		const std::string& filename,
		unsigned int lineNum)
		: mMessage(message)
		, mFileName(filename)
		, mLineNum(lineNum)
	{
		mFormatMessage = ToString();
	}

	exception_base::~exception_base()
	{

	}

	void exception_base::Print() const
	{
		std::cerr << ToString();
	}

	std::string exception_base::ToString() const
	{
		std::ostringstream ss;
		ss.setf(std::ios::left, std::ios::adjustfield);

		std::string s(78, '-');
		std::string s1("{exception begin");
		std::string s2("}exception end");
		
		ss << std::endl;

		const int nWidth = 8;

		ss << s1 << "\n";

		ss << "| ";
		ss.width(nWidth);
		ss << "Reason:" << mMessage << std::endl;

		ss << "| ";
		ss.width(nWidth);
		ss << "File:" << mFileName << std::endl;

		ss << "| ";
		ss.width(nWidth);
		ss << "Line:" << mLineNum << std::endl;

		ss << s2 << std::endl;

		return ss.str();
	}

	const std::string& exception_base::File() const
	{
		return mFileName;
	}

	unsigned int exception_base::Line() const
	{
		return mLineNum;
	}

	const char * exception_base::what() const
	{
#ifdef EXCEPTION_WHAT_FORMAT_STRING
		return mFormatMessage.c_str();
#else
		return mMessage.c_str();
#endif
	}
}

namespace Study_Boost
{
	boost_exception* boost_exception::m_hInstance = NULL;
	
	boost_exception* boost_exception::InitInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_exception;
		}
		return m_hInstance;
	}
	boost_exception* boost_exception::GetInstance()
	{
		if(m_hInstance == NULL)
		{
			m_hInstance = new boost_exception;
		}
		return m_hInstance;
	}
	
	void boost_exception::ExitInstance()
	{
		if(m_hInstance)
		{
			delete m_hInstance;
			m_hInstance = NULL;
		}
	}

	void boost_exception::runTest()
	{
		_test_error_info_1();
		_test_io();
	}


	DEFINE_ERROR_INFO(int, ActorError)
	typedef boost::error_info<struct tag_my_info_str, std::string> my_info_str;
	struct my_error: virtual boost::exception, virtual std::exception{};
	
	struct my_exception: virtual boost::exception, virtual exception_base{};

	void f3() throw(exception_base)
	{
		throw VR_BASE_EXCEPTION("my exception");
	}

	void f4()
	{
		throw std::bad_function_call();
	}
	
	void f41()
	{
		f4();
	}

	struct error : virtual std::exception, virtual boost::exception { };
	struct file_error : virtual error { };
	struct file_open_error: virtual file_error { };
	struct file_read_error: virtual file_error { };


	void boost_exception::_test_error_info_1()
	{
		try
		{
			BOOST_THROW_EXCEPTION(my_error() << boost::errinfo_errno(123123)<< my_info_str("adfa")<< boost::errinfo_api_function("f1 Failed!") 
				<< ActorError(222));
		}
		catch (my_error& e)
		{
			std::string const* str = boost::get_error_info<my_info_str>(e);
			char const** str1 = boost::get_error_info<boost::errinfo_api_function>(e);

			LOG(WARNING) << *str;

			LOG(WARNING) << boost::diagnostic_information(e);
		}

		try
		{
			BOOST_THROW_EXCEPTION(my_error());
		}
 		catch (my_error& e)
		{
 			LOG(WARNING) << *boost::get_error_info<boost::throw_function>(e)
 				<< *boost::get_error_info<boost::throw_file>(e)
 				<< " At Line [" << *boost::get_error_info<boost::throw_line>(e);
 		}

		try
		{
			f3();
		}
		catch(exception_base& m)
		{
			LOG(WARNING) << m.ToString() << std::endl << m.what();
		}

		try
		{
			f4();
		}
		catch(std::exception& m)
		{
			LOG(WARNING) << m.what();
		}

		try
		{
			//VR_THROW_EXCEPTION(my_error() << errorFunction("111") << errorFunction("222")
				//<< errorReason("123") << errorReason("1234"), 123);

			BOOST_THROW_EXCEPTION(my_error());
		}
		catch(boost::exception& m)
		{
			LOG(WARNING) << boost::diagnostic_information(m);
		}

		try{
			VR_THROW_EXCEPTION_REASON(vire_exception() << errorCode(123123), 111, "adfasdfa");
		}
		catch(boost::exception& m)
		{
			LOG(WARNING) << boost::diagnostic_information(m);
		}

		try
		{
			BOOST_THROW_EXCEPTION(vire_exception() 
				<< errorCode(123123) << errorKK(1231));
// 			BOOST_THROW_EXCEPTION(vire_exception() 
// 				<< errorCode(123123) << 
// 				errorLine(__LINE__) << errorFile(__FILE__));
		}
		catch(boost::exception& m)
		{
			LOG(WARNING) << boost::diagnostic_information(m);
		}


		try
		{
			f41();
		}
		catch(...)
		{

		}
	}

	namespace test_io
	{
		typedef boost::error_info<struct tag_file_name_src,std::string> errinfo_src_file_name;
		typedef boost::error_info<struct tag_file_name_dst,std::string> errinfo_dst_file_name;

		char const data[] = "example";
		size_t const data_size = sizeof(data);

		class error: public virtual std::exception, public virtual boost::exception
		{
		public:

			char const *
				what() const throw()
			{
				return "example_io error";
			}

		protected:

			~error() throw()
			{
			}
		};

		struct open_error: virtual error { };
		struct read_error: virtual error { };
		struct write_error: virtual error { };
		struct fopen_error: virtual open_error { };
		struct fread_error: virtual read_error { };
		struct fwrite_error: virtual write_error { };

		boost::shared_ptr<FILE>
			my_fopen( char const * name, char const * mode )
		{
			if( FILE * f = ::fopen(name,mode) )
				return boost::shared_ptr<FILE>(f,fclose);
			else
				BOOST_THROW_EXCEPTION(fopen_error() <<
				boost::errinfo_errno    (errno) <<
				boost::errinfo_file_name(name) <<
				boost::errinfo_file_open_mode(mode) <<
				boost::errinfo_api_function("fopen"));
		}

		void
			my_fread( void * buffer, size_t size, size_t count, boost::shared_ptr<FILE> const & stream )
		{
			assert(stream);
			if( count!=fread(buffer,size,count,stream.get()) || ferror(stream.get()) )
				BOOST_THROW_EXCEPTION(fread_error() <<
				boost::errinfo_api_function("fread") <<
				boost::errinfo_errno(errno));
		}

		void
			my_fwrite( void const * buffer, size_t size, size_t count, boost::shared_ptr<FILE> const & stream )
		{
			assert(stream);
			if( count!=fwrite(buffer,size,count,stream.get()) || ferror(stream.get()) )
				BOOST_THROW_EXCEPTION(fwrite_error() <<
				boost::errinfo_api_function("fwrite") <<
				boost::errinfo_errno(errno));
		}

		void
			reset_file( char const * file_name )
		{
			(void) my_fopen(file_name,"wb");
		}

		void
			create_data( char const * file_name )
		{
			boost::shared_ptr<FILE> f = my_fopen(file_name,"wb");
			my_fwrite( data, 1, data_size, f );
		}

		void
			copy_data( char const * src_file_name, char const * dst_file_name )
		{
			boost::shared_ptr<FILE> src = my_fopen(src_file_name,"rb");
			boost::shared_ptr<FILE> dst = my_fopen(dst_file_name,"wb");
			try
			{
				char buffer[data_size];
				my_fread( buffer, 1, data_size, src );
				my_fwrite( buffer, 1, data_size, dst );
			}
			catch(
				boost::exception & x )
			{
				/*if( boost::weak_ptr<FILE> const * f = boost::get_error_info<boost::errinfo_file_handle>(x) )
					if( boost::shared_ptr<FILE> fs = f->lock() )
					{
						if( fs==src )
							x << boost::errinfo_file_name(src_file_name);
						else if( fs==dst )
							x << boost::errinfo_file_name(dst_file_name);
					}
					x <<
						errinfo_src_file_name(src_file_name) <<
						errinfo_dst_file_name(dst_file_name);
					throw;*/
			}
		}

		void
			dump_copy_info( boost::exception const & x )
		{
			if( std::string const * src = boost::get_error_info<errinfo_src_file_name>(x) )
				std::cerr << "Source file name: " << *src << "\n";
			if( std::string const * dst = boost::get_error_info<errinfo_dst_file_name>(x) )
				std::cerr << "Destination file name: " << *dst << "\n";
		}

		void
			dump_file_info( boost::exception const & x )
		{
			if( std::string const * fn = boost::get_error_info<boost::errinfo_file_name>(x) )
				std::cerr << "File name: " << *fn << "\n";
		}

		void
			dump_clib_info( boost::exception const & x )
		{
			if( int const * err=boost::get_error_info<boost::errinfo_errno>(x) )
				std::cerr << "OS error: " << *err << "\n";
			if( char const * const * fn=boost::get_error_info<boost::errinfo_api_function>(x) )
				std::cerr << "Failed function: " << *fn << "\n";
		}

		void
			dump_all_info( boost::exception const & x )
		{
			std::cerr << "-------------------------------------------------\n";
			dump_copy_info(x);
			dump_file_info(x);
			dump_clib_info(x);
			std::cerr << "\nOutput from diagnostic_information():\n";
			std::cerr << diagnostic_information(x);
		}
	}
	

	void boost_exception::_test_io()
	{
		using namespace test_io;
		
		try
		{
			create_data( "tmp1.txt" );
			copy_data( "tmp1.txt", "tmp2.txt" ); //This should succeed.

			reset_file( "tmp1.txt" ); //Creates empty file.
			try
			{
				copy_data( "tmp1.txt", "tmp2.txt" ); //This should fail, tmp1.txt is empty.
			}
			catch(
				read_error & x )
			{
				std::cerr << "\nCaught 'read_error' exception.\n";
				dump_all_info(x);
			}

			remove( "tmp1.txt" );
			remove( "tmp2.txt" );
			try
			{
				copy_data( "tmp1.txt", "tmp2.txt" ); //This should fail, tmp1.txt does not exist.
			}
			catch(
				open_error & x )
			{
				std::cerr << "\nCaught 'open_error' exception.\n";
				dump_all_info(x);
			}
		}
		catch(
			... )
		{
			std::cerr << "\nCaught unexpected exception!\n";
			std::cerr << boost::current_exception_diagnostic_information();
		}
	}
}