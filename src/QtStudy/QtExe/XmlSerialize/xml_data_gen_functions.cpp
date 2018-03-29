#include "xml_data_gen_functions.h"
#include <wchar.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>

#if defined(WIN32) && !defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

namespace xml_data_gen_functions
{
	bool getApplicationFileDir( char* szPath, unsigned int nSize)
	{
		if (szPath == NULL)
		{
			return false;
		}

		char szFullPath[MAX_PATH];
		char szDir[_MAX_DIR];
		char szDrive[_MAX_DRIVE];

		::GetModuleFileName(NULL, szFullPath, MAX_PATH);
		_splitpath(szFullPath, szDrive, szDir, NULL, NULL);

		char szDstPath[MAX_PATH];
		_makepath(szDstPath, szDrive, szDir, NULL, NULL);

		return !strcpy_s(szPath, nSize, szDstPath);
	}

	bool nomalizePath(char* szPath )
	{
		if (szPath == NULL || strlen(szPath) == 0)
		{
			return false;
		}

		char _SEPARATORS = '\\';
		struct find : public std::unary_function<char, bool>
		{
			char _findChar;
			find(char fch)
			{
				_findChar = fch;
			}
			bool operator()(char ch)const
			{
				if (ch == _findChar)
				{
					return true;
				}
				return false;
			}
		};

		std::replace_if(szPath, szPath + strlen(szPath), find('\\'), '/');

		return true;
	}

	bool cleanupFileString(char* strFileOrDir)
	{
		if (strFileOrDir == NULL || strlen(strFileOrDir) == 0)
		{
			return false;
		}

		if(!nomalizePath(strFileOrDir))
		{
			return false;
		}

		// get rid of trailing separators
		if (strFileOrDir[strlen(strFileOrDir)-1] == '/')
		{
			strFileOrDir[strlen(strFileOrDir)-1] = '\0';
		}

		return true;
	}

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

	void genString(std::string& strOut, bool bchinese, int nsize)
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

		strOut = convertStringCurrentCodePageWC_2_MB(strRet);
	}

#ifdef XMLSERIALIZE_QT_SUPPORT
	void genString(QString& strOut, bool bchinese, int nsize)
	{
		std::string strTemp;
		genString(strTemp, bchinese, nsize);

		strOut = QString::fromLocal8Bit(strTemp.c_str());
	}
#endif
	
	void output_msg( const char* msg, State s )
	{
		std::stringstream ss;

		switch (s)
		{
		case S_Begin:
			ss << std::endl << "===============Begin " << msg;
			break;
		case S_SUCCESS:
			ss << "===============" << msg << " Success!!!";
			break;
		case S_Failed:
			ss << "===============" << msg << " Faild!!!";
			break;
		default:
			break;
		}

		ss << "===============" << std::endl;

		std::cout << ss.str();
	}
}