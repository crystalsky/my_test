#include "data_gen_functions.h"

#include <wchar.h>
#include <iostream>

#if defined(WIN32) && !defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

namespace data_gen_functions
{
	std::string convertStringCurrentCodePageWC_2_MB( const wchar_t* source, unsigned sourceLength )
	{
		if (sourceLength == 0)
		{
			return std::string();
		}

		int destLen = WideCharToMultiByte(CP_ACP, 0, source, sourceLength, 0, 0, 0, 0);
		if (destLen <= 0)
		{
			std::cout << "Cannot convert multi-byte string to UTF-8." << std::endl;
			return std::string();
		}

		std::string sDest(destLen, '\0');
		destLen = WideCharToMultiByte(CP_ACP, 0, source, sourceLength, &sDest[0], destLen, 0, 0);

		return sDest;
	}

	std::string convertStringCurrentCodePageWC_2_MB( const std::wstring& s )
	{
		return convertStringCurrentCodePageWC_2_MB(s.c_str(), s.length());
	}

	unsigned int genInt(int nRange)
	{
		static bool b = true;
		if (b)
		{
			srand(time_t());
			b = false;
		}
		int nVal = rand();
		if (nRange <= 0)
		{
			return nVal;
		}
		return nVal % nRange;
	}

	float genFloat()
	{
		return 1.234f * genInt();
	}

	double genDouble()
	{
		return 1.123123123123 * genInt();
	}

	bool genBool()
	{
		return genInt() % 2 == 1;
	}

	std::string genString( bool bchinese, int nsize /*= 10*/ )
	{
		const std::wstring pStrChines = L"这是中文哦，不知道可不可以用啊，测试一下！";
		const std::wstring pStr = L"abcdefghigk=23929848918*#$*$%";

		std::wstring strRet;
		for (int i = 0; i < nsize; ++i)
		{
			int nSize = bchinese ? pStrChines.length() : pStr.length();
			int nRand = genInt(nSize);
			std::wstring ps = bchinese ? pStrChines : pStr;
			strRet += ps[nRand];
		}

		std::string strOut = convertStringCurrentCodePageWC_2_MB(strRet);
		return strOut;
	}

	void genString(std::string& strOut, bool bchinese, int nsize)
	{
		strOut = genString(bchinese, nsize);
	}


	void genString(QString& strOut, bool bchinese, int nsize)
	{
		std::string strTemp = genString(bchinese, nsize);
		strOut = QString::fromLocal8Bit(strTemp.c_str());
	}
}
