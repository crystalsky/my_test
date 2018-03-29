#ifndef data_gen_functions_h__
#define data_gen_functions_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <sstream>
#include <QtCore>

namespace data_gen_functions
{
	unsigned int genInt(int nRange = 0);

	float genFloat();

	double genDouble();

	bool genBool();

	std::string genString(bool bchinese, int nsize = 10);

	void genString(std::string& strOut, bool bchinese = false, int nsize = 10);

	void genString(QString& strOut, bool bchinese = false, int nsize = 10);
}

namespace data_gen_functions
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
}

#define EQUAL_DOUBLE_VALUE (1e-8)		//定义双精度浮点数比较最小值
#define CHECK_DOUBLE_VALUE_EQUAL(a,b) ((abs(a - b)) <= EQUAL_DOUBLE_VALUE)

#define EQUAL_FLOAT_VALUE (1e-6)		//定义双精度浮点数比较最小值
#define CHECK_FLOAT_VALUE_EQUAL(a,b) ((abs(a - b)) <= EQUAL_FLOAT_VALUE)


#endif // data_gen_functions_h__
