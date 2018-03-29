#include "Strategy_By_FunctionPointer.h"
#include <assert.h>

namespace StrategyFunctionPointer
{
	class GameCharacter;
	int defaultHealthValue(const GameCharacter& gc)
	{
		std::cout << "defaultHealthValue" << std::endl;
		return 10;
	}
	class GameCharacter
	{
	public:
		typedef int (*HealthCacFunc)(const GameCharacter& gc);
		explicit GameCharacter(HealthCacFunc func = defaultHealthValue)
		{
			setHealthCacFunc(func);
		}
		virtual ~GameCharacter(){}
	public:
		int getHealthValue()const			
		{
			return m_HealthCacFunc(*this);
		}

		void setHealthCacFunc(HealthCacFunc func)//! 可以在运行期变更函数的
		{
			assert(func != NULL);
			m_HealthCacFunc = func;
		}

	private:
		HealthCacFunc m_HealthCacFunc;
	};

	class EvilBadGuy : public GameCharacter
	{
	public:
		explicit EvilBadGuy(HealthCacFunc func = defaultHealthValue) : GameCharacter(func)
		{

		}
	};
	int loseHealthQuickly(const GameCharacter& gc)
	{
		std::cout<< "loseHealthQuickly" << std::endl;
		return 20;
	}
	int loseHealthSlowly(const GameCharacter& gc)
	{
		std::cout<< "loseHealthSlowly" << std::endl;
		return 30;
	}

	void test()
	{
		EvilBadGuy ev1(loseHealthQuickly);
		ev1.getHealthValue();

		EvilBadGuy ev2(loseHealthSlowly);
		ev2.getHealthValue();
	}
}


IMPLEMENT_REFLECTED_CLASS(Strategy_By_FunctionPointer)
Strategy_By_FunctionPointer::Strategy_By_FunctionPointer()
{
	
}

Strategy_By_FunctionPointer::~Strategy_By_FunctionPointer()
{
	
}

void Strategy_By_FunctionPointer::run()
{
	StrategyFunctionPointer::test();
}
