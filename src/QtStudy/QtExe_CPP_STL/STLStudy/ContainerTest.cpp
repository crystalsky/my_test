#include "ContainerTest.h"
#include <vector>
#include <list>
#include <algorithm>
#include <TTimePrint.h>

IMPLEMENT_REFLECTED_CLASS(ContainerTest)
ContainerTest::ContainerTest()
{
	
}

ContainerTest::~ContainerTest()
{
	
}

void ContainerTest::run()
{
	//std::cout << "<<<_comapare_list_2_vector begin" << std::endl;
	//_comapare_list_2_vector();
	//std::cout << ">>>_comapare_list_2_vector end" << std::endl;
	std::cout << std::endl;
	_compare_vector();
	std::cout << std::endl;
	_938_find_char();
	std::cout << std::endl;
	_939_word_count();
	std::cout << std::endl;
	_vector_test();
}

void ContainerTest::_compare_vector()
{
	int ar1[] = {1, 3, 5, 7, 9, 12};
	int ar2[] = {0, 2, 4, 6, 8, 10, 12};
	int ar3[] = {1, 3, 9};
	int ar4[] = {1, 3, 9, 12};
	int ar5[] = {1, 3, 5, 7, 9, 12};
	int ar6[] = {1, 3, 4};

	std::vector<int> vec1(ar1, ar1 + sizeof(ar1) / sizeof(int));
	std::vector<int> vec2(ar2, ar2 + sizeof(ar2) / sizeof(int));
	std::vector<int> vec3(ar3, ar3 + sizeof(ar3) / sizeof(int));
	std::vector<int> vec4(ar4, ar4 + sizeof(ar4) / sizeof(int));
	std::vector<int> vec5(ar5, ar5 + sizeof(ar5) / sizeof(int));
	std::vector<int> vec6(ar6, ar6 + sizeof(ar6) / sizeof(int));

	std::cout << "vec1 < vec2 = " 
		<< (vec1 < vec2 ? "true" : "false") << std::endl;
	std::cout << "vec1 < vec3 = " 
		<< (vec1 < vec3 ? "true" : "false") << std::endl;
	std::cout << "vec1 < vec4 = " 
		<< (vec1 < vec4 ? "true" : "false") << std::endl;
	std::cout << "vec1 == vec4 = " 
		<< (vec1 == vec4 ? "true" : "false") << std::endl;
	std::cout << "vec1 == vec5 = " 
		<< (vec1 == vec5 ? "true" : "false") << std::endl;
	std::cout << "vec1 < vec6 = " 
		<< (vec1 < vec6 ? "true" : "false") << std::endl;
}

void ContainerTest::_comapare_list_2_vector()
{
	std::vector<int> vec;
	std::list<int> lst;
	int ival = 0;

	std::cout << "Enter some integers for vecotr(Ctrl+Z) to end"
		<< std::endl;

	while (std::cin >> ival)
	{
		vec.push_back(ival);
	}

	std::cin.clear();

	std::cout << "Enter some integers for list(Ctrl+Z) to end"
		<< std::endl;

	while (std::cin >> ival)
	{
		lst.push_back(ival);
	}

	std::cin.clear();

	std::vector<int>::iterator ivec = vec.begin();
	std::list<int>::iterator ilst = lst.begin();
	while (ivec != vec.end() && ilst != lst.end())
	{
		if (*ivec != *ilst)
		{
			break;
		}

		ivec++;
		ilst++;
	}

	if (ivec == vec.end() && ilst == lst.end())
	{
		std::cout << "list == vec" << std::endl;
	}
	else
	{
		std::cout << "list != vec" << std::endl;
	}
}

void ContainerTest::_938_find_char()
{
	std::string str = "ab3dbE3dc2C6";

	std::string numerics = "123456789";

	std::string strLetters;
	{
		std::string str2 = "abcdefghijklmnopqrstuvwxyz";

		std::string strupper(str2);
		std::string::iterator it = std::transform(str2.begin(), str2.end(), strupper.begin(), toupper);

		strLetters = str2 + " " + strupper;
	}
	
	{//1
		int nPos = 0;
		while ((nPos = str.find_first_of(numerics, nPos)) != std::string::npos)
		{
			std::cout << "found number at:" << nPos 
				<< " elements is: " << str[nPos] << std::endl;

			nPos++;
		}

		nPos = 0;
		while ((nPos = str.find_first_of(strLetters, nPos)) != std::string::npos)
		{
			std::cout << "found characactor at:" << nPos 
				<< " elements is: " << str[nPos] << std::endl;

			nPos++;
		}
	}

	{//2
		int nPos = 0;
		while ((nPos = str.find_first_not_of(strLetters, nPos)) != std::string::npos)
		{
			std::cout << "found number at:" << nPos 
				<< " elements is: " << str[nPos] << std::endl;

			nPos++;
		}

		nPos = 0;
		while ((nPos = str.find_first_not_of(numerics, nPos)) != std::string::npos)
		{
			std::cout << "found characactor at:" << nPos 
				<< " elements is: " << str[nPos] << std::endl;

			nPos++;
		}
	}
}

void ContainerTest::_939_word_count()
{
	std::string line1 = "We were her pride of 10 she named us:";
	std::string line2 = "Benjamin, Phoenix, the Prodigal";
	std::string line3 = "and Perspicacious pacific Suzanne";

	std::string sentense = line1 + ' ' + line2 + ' ' + line3;

	int nWordCount(0), nMaxLenWord(0), nMinLenWord(0);
	std::list<std::string> listMaxlengthWord;
	std::list<std::string> listMinLenghtWorkdList;

	int nStartPos = 0, nEndPos = 0;

	std::string strFind = " :,\n\r\t\v\f";
	while ((nStartPos = sentense.find_first_not_of(strFind, nEndPos)) !=
		std::string::npos)
	{
		int nWordLen = 0;
		nEndPos = sentense.find_first_of(strFind, nStartPos);
		if (nEndPos == std::string::npos)
		{
			nWordLen = sentense.size() - nStartPos;
		}
		else
		{
			nWordLen = nEndPos - nStartPos;
		}

		const std::string strWord = sentense.substr(nStartPos, nWordLen);
		std::cout << strWord << std::endl;

		nWordCount++;
		if (nWordCount == 1)
		{
			nMaxLenWord = strWord.length();
			nMinLenWord = strWord.length();
			listMaxlengthWord.push_back(strWord);
			listMinLenghtWorkdList.push_back(strWord);
		}
		else
		{
			if (nWordLen > nMaxLenWord)
			{
				nMaxLenWord = nWordLen;
				listMaxlengthWord.clear();
				listMaxlengthWord.push_back(strWord);
			}
			else if (nWordLen == nMaxLenWord)
			{
				listMaxlengthWord.push_back(strWord);
			}
			
			if (nWordLen < nMinLenWord)
			{
				nMinLenWord = nWordLen;
				listMinLenghtWorkdList.clear();
				listMinLenghtWorkdList.push_back(strWord);
			}
			else if(nWordLen == nMinLenWord)
			{
				listMinLenghtWorkdList.push_back(strWord);
			}
		}
	}

	struct outputstring
	{
		void operator()(const std::string& str)
		{
			std::cout << str << " ";
		}
	};
	std::cout << "Word Count:" << nWordCount << std::endl;
	std::cout << "longest words:";
	std::for_each(listMaxlengthWord.begin(), listMaxlengthWord.end(), outputstring());

	std::cout << std::endl << "minmal words:";
	std::for_each(listMinLenghtWorkdList.begin(), listMinLenghtWorkdList.end(), outputstring());
	std::cout << std::endl;
}

#include <stack>
void ContainerTest::_stack()
{
	std::stack<int> stk;

	//std::priority_queue
}

void ContainerTest::_vector_test()
{
	int ar1[] = {1, 3, 5, 7, 9, 12};
	int ar2[] = {0, 2, 4, 6, 8, 10, 321,1112,642};

	std::vector<int> v1(ar1, ar1 + sizeof(ar1)/sizeof(int));

	std::vector<int> v2;
	v2.assign(ar2, ar2 + sizeof(ar2) / sizeof(int));
	std::vector<int> v3(3000000, 10);

	TTRestart;
	std::vector<int> v3assign;
	v3assign.assign(v3.begin(), v3.end());
	TTPrintAndRestart("v3assign Assign");

	std::vector<int> v4;
	std::copy(v3.begin(), v3.end(), std::back_inserter(v4));
	TTPrintAndRestart("copy v3 to v4");

	std::vector<int> v5;
	v5.insert(v5.begin(), v3.begin(), v3.end());
	TTPrintAndRestart("v5 insert v3");

	std::list<int> list1;
	list1.insert(list1.begin(), v3.begin(), v3.end());
	TTPrintAndRestart("list1 insert v3");
}
