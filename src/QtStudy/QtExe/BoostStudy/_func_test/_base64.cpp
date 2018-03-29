#include "_base64.h"
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <xfunctional>


IMPLEMENT_REFLECTED_CLASS(_base64)
_base64::_base64()
{
	
}

_base64::~_base64()
{
	
}

template<typename CharType>
void test_base64(unsigned int size){
	CharType rawdata[150];
	CharType * rptr;
	for(rptr = rawdata + size; rptr-- > rawdata;)
		*rptr = static_cast<CharType>(std::rand()& 0xff);

	// convert to base64
	typedef std::vector<CharType> text_base64_type;
	text_base64_type text_base64;

	typedef 
		boost::archive::iterators::insert_linebreaks<
			boost::archive::iterators::base64_from_binary<
				boost::archive::iterators::transform_width<
					CharType *
					,6
					,sizeof(CharType) * 8
				>
			> 
			,76
		> 
		translate_out;

	std::copy(
		translate_out(BOOST_MAKE_PFTO_WRAPPER(static_cast<CharType *>(rawdata))),
		translate_out(BOOST_MAKE_PFTO_WRAPPER(rawdata + size)),
		std::back_inserter(text_base64)
		);

	// convert from base64 to binary and compare with the original 
	typedef 
		boost::archive::iterators::transform_width<
		boost::archive::iterators::binary_from_base64<
		boost::archive::iterators::remove_whitespace<
		typename text_base64_type::iterator
		>
		>,
		sizeof(CharType) * 8,
		6
		> translate_in;

	bool b = 
		std::equal(
		rawdata,
		rawdata + size,
		translate_in(BOOST_MAKE_PFTO_WRAPPER(text_base64.begin()))
		);
}

int Base64Encode(const char* pdata, int nLen, std::string& strOut)
{
	strOut.clear();

	try
	{
		using namespace boost::archive::iterators;
		typedef 
			base64_from_binary<
				transform_width<char *, 6, 8>
			> translate_out;

		std::copy(
			translate_out(BOOST_MAKE_PFTO_WRAPPER(pdata + 0)),
			translate_out(BOOST_MAKE_PFTO_WRAPPER(pdata + nLen)),
			std::back_inserter(strOut)
			);

		size_t num = (3 - nLen % 3) % 3;
		for (size_t i = 0; i < num; ++i)
		{
			strOut.push_back('=');
		}

		return strOut.length();
	}
	catch(...)
	{
		return -2;
	}
	
	return -1;
}


int Base64Decode(const std::string& strIN, char** pdata)
{
	if (strIN.empty())
	{
		return -1;
	}

	try
	{
		//解码的输入一定会比输出的大
		*pdata = new char[strIN.length()];
		memset(*pdata, 0, strIN.length());

		using namespace boost::archive::iterators;
		typedef 
			transform_width<
				binary_from_base64<
					std::string::const_iterator>,
					8,
					6
				> 
				translate_in;

		char* pout = std::copy(
			translate_in(strIN.begin()),
			translate_in(strIN.end()),
			*pdata
			);

		size_t nEquqlSize = std::count_if(
			strIN.begin(), 
			strIN.end(), 
			std::bind1st(std::equal_to<char>(), '='));

		return pout - *pdata - nEquqlSize;
	}
	catch(...)
	{
		delete *pdata;
		return -2;
	}

	return -1;
}


void _base64::run()
{
	const char* strInput = "http://192.168.0.36";
	std::string strout;

	Base64Encode(strInput, strlen(strInput), strout);

	char* pData = NULL;
	int nLen = Base64Decode(strout, &pData);
	if (nLen > 0)
	{

		delete []pData;
	}
	

	test_base64<char>(1);
	test_base64<char>(2);
	test_base64<char>(3);
	test_base64<char>(4);
	test_base64<char>(150);
// #ifndef BOOST_NO_CWCHAR
// 	test_base64<wchar_t>(1);
// 	test_base64<wchar_t>(2);
// 	test_base64<wchar_t>(3);
// 	test_base64<wchar_t>(4);
// 	test_base64<wchar_t>(150);
// #endif
}
