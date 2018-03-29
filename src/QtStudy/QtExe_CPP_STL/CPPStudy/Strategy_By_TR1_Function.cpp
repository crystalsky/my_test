#include "Strategy_By_TR1_Function.h"
#include <assert.h>
#include <functional>

namespace StrategyByTR1Function
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
		typedef std::tr1::function<int (const GameCharacter&)> HealthCalcFunction;
		explicit GameCharacter(HealthCalcFunction func = defaultHealthValue)
		{
			setHealthCacFunc(func);
		}
		virtual ~GameCharacter(){}
	public:
		int getHealthValue()const			
		{
			return m_HealthCacFunc(*this);
		}

		void setHealthCacFunc(HealthCalcFunction func)//! 可以在运行期变更函数的
		{
			assert(func != NULL);
			m_HealthCacFunc = func;
		}

	private:
		HealthCalcFunction m_HealthCacFunc;
	};
	
	short calcHealth(const GameCharacter& f)
	{
		std::cout << "calcHealth" << std::endl;
		return 40;
	}

	struct HealthCaculator
	{
		int operator()(const GameCharacter& r)const
		{
			std::cout << "HealthCaculator" << std::endl;
			return 44;
		}
	};

	class GameLevel
	{
	public:
		float health(const GameCharacter&)const
		{
			std::cout << "GameLevel::health" << std::endl;
			return 1.0;
		}
	};

	class EvilBadGuy : public GameCharacter
	{
	public:
		explicit EvilBadGuy(HealthCalcFunction func = defaultHealthValue) : GameCharacter(func)
		{

		}
	};

	class EvilCandyCharactor : public GameCharacter
	{
	public:
		explicit EvilCandyCharactor(HealthCalcFunction func = defaultHealthValue) : GameCharacter(func)
		{

		}
	};

	class Evil2 : public GameCharacter
	{
	public:
		explicit Evil2(HealthCalcFunction func = defaultHealthValue) : GameCharacter(func)
		{

		}
	};

	static void test()
	{
		EvilBadGuy ebg1(calcHealth);
		ebg1.getHealthValue();

		EvilCandyCharactor ecc1(HealthCaculator());
		//ecc1.getHealthValue();

		GameLevel gl;
		Evil2 e2(std::tr1::bind(&GameLevel::health, gl, std::tr1::placeholders::_1));
		e2.getHealthValue();
	}
}

IMPLEMENT_REFLECTED_CLASS(Strategy_By_TR1_Function)
Strategy_By_TR1_Function::Strategy_By_TR1_Function()
{
	
}

Strategy_By_TR1_Function::~Strategy_By_TR1_Function()
{
	
}

void Strategy_By_TR1_Function::run()
{
	StrategyByTR1Function::test();
}
