#ifndef xml_data_gen_functions_h__
#define xml_data_gen_functions_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <sstream>

#define XMLSERIALIZE_NO_BOOST
#include <XmlSerialize.h>


#ifdef XMLSERIALIZE_QT_SUPPORT
	#include <QtCore>
#endif

namespace xml_data_gen_functions
{
	unsigned int genInt(int nRange = 0);

	float genFloat();

	double genDouble();

	bool genBool();

	void genString(std::string& strOut, bool bchinese = false, int nsize = 10);

#ifdef XMLSERIALIZE_QT_SUPPORT
	void genString(QString& strOut, bool bchinese = false, int nsize = 10);
#endif

	bool getApplicationFileDir( char* szPath, unsigned int nSize);

	bool nomalizePath(char* szPath );

	bool cleanupFileString(char* strFileOrDir);
}

namespace xml_data_gen_functions
{
	template <typename T, typename Container>
	struct GenData
	{
		static void gendata(Container& c, int nSize = 1)
		{
			if (nSize < 1)
			{
				nSize = 1;
			}

			for (int i = 0; i < nSize; ++i)
			{
				c.push_back(T());
			}
		}
	};

	template <typename T>
	struct GenData<T*, std::vector<T*>>
	{
		static void gendata(std::vector<T*>& c, int nSize = 1)
		{
			if (nSize < 1)
			{
				nSize = 1;
			}

			for (int i = 0; i < nSize; ++i)
			{
				c.push_back(new T(nSize));
			}
		}
	};

	template <typename T>
	struct GenData<T*, std::list<T*>>
	{
		static void gendata(std::list<T*>& c, int nSize = 1)
		{
			if (nSize < 1)
			{
				nSize = 1;
			}

			for (int i = 0; i < nSize; ++i)
			{
				c.push_back(new T(nSize));
			}
		}
	};

#ifdef XMLSERIALIZE_QT_SUPPORT
	template <typename T>
	struct GenData<T*, QVector<T*>>
	{
		static void gendata(QVector<T*>& c, int nSize = 1)
		{
			if (nSize < 1)
			{
				nSize = 1;
			}

			for (int i = 0; i < nSize; ++i)
			{
				c.push_back(new T(nSize));
			}
		}
	};

	template <typename T>
	struct GenData<T*, QList<T*>>
	{
		static void gendata(QList<T*>& c, int nSize = 1)
		{
			if (nSize < 1)
			{
				nSize = 1;
			}

			for (int i = 0; i < nSize; ++i)
			{
				c.push_back(new T(nSize));
			}
		}
	};
#endif
}

#define EQUAL_DOUBLE_VALUE (1e-8)		//定义双精度浮点数比较最小值
#define CHECK_DOUBLE_VALUE_EQUAL(a,b) ((abs(a - b)) <= EQUAL_DOUBLE_VALUE)

#define EQUAL_FLOAT_VALUE (1e-6)		//定义双精度浮点数比较最小值
#define CHECK_FLOAT_VALUE_EQUAL(a,b) ((abs(a - b)) <= EQUAL_FLOAT_VALUE)

namespace xml_data_gen_functions
{
	struct GenObject
	{
		GenObject()
		{
			genString(m_strEnglish);
			genString(m_strChinese, true);

			m_chVal = genInt();
			m_uchval = genInt();
			m_sVal = genInt();
			m_usVal = genInt();
			m_nIntVal = genInt();
			m_unIntVal = genInt();

			m_n64Val = genInt();
			m_un64Val = genInt();

			m_bVal = genBool();
			m_doubleVal = genDouble();
			m_floatVal = genFloat();
		}

		inline bool operator == (const GenObject& other)const
		{
			return m_strEnglish == other.m_strEnglish &&
				m_strChinese == other.m_strChinese &&
				m_chVal == other.m_chVal && 
				m_uchval == other.m_uchval && 
				m_sVal == other.m_sVal && 
				m_usVal == other.m_usVal && 
				m_nIntVal == other.m_nIntVal && 
				m_unIntVal == other.m_unIntVal && 
				m_n64Val == other.m_n64Val && 
				m_un64Val == other.m_un64Val && 
				m_bVal == other.m_bVal && 
				CHECK_DOUBLE_VALUE_EQUAL(m_doubleVal, other.m_doubleVal) && 
				CHECK_FLOAT_VALUE_EQUAL(m_floatVal, other.m_floatVal);
		}

#ifdef XMLSERIALIZE_QT_SUPPORT
		qint8 m_chVal;
		quint8 m_uchval;

		qint16 m_sVal;
		quint16 m_usVal;

		qint32	m_nIntVal;
		quint32 m_unIntVal;

		qint64 m_n64Val;
		quint64 m_un64Val;

		QString m_strEnglish;
		QString m_strChinese;

		bool m_bVal;
		qreal m_doubleVal;
		float m_floatVal;
#else
		char m_chVal;
		unsigned char m_uchval;

		short m_sVal;
		unsigned short m_usVal;

		int	m_nIntVal;
		unsigned int m_unIntVal;

		__int64 m_n64Val;
		unsigned __int64 m_un64Val;

		std::string m_strEnglish;
		std::string m_strChinese;

		bool m_bVal;
		double m_doubleVal;
		float m_floatVal;
#endif
	};
}

namespace xml_data_gen_functions
{
	enum State
	{
		S_Begin,
		S_SUCCESS,
		S_Failed,
	};

	void output_msg(const char* msg, State s);
}

#endif // xml_data_gen_functions_h__