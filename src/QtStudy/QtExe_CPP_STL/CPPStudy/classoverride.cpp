#include "classoverride.h"

class NoMementClass
{
public:
	NoMementClass(){}
};

class ordClass
{
public:
	ordClass(){}
	void ok(){}
};

class baseiv
{
public:
	baseiv(){}

	void setName(const std::string& strName)
	{
		_name = strName;
	}

	virtual void mf1(){}
	virtual void mf1(int){}
	virtual void mf2(){}
	void mf3(){}
	void mf3(double){}
private:
	std::string _name;
};

class baseiv_A : public baseiv
{
public:
	baseiv_A(){}
	//using baseiv::mf1;	
	using baseiv::mf3;//TODO：让基类名为mf1和mf3的所有东西在继承类的作用域内都可见

	void setName(const std::string& strName)
	{
		_name = strName;
	}

	virtual void mf1(){}
	void mf3(){}
	void mf4(){}

private:
	std::string _name;
};


IMPLEMENT_REFLECTED_CLASS(classoverride)
classoverride::classoverride()
{
	
}

classoverride::~classoverride()
{
	
}

void classoverride::run()
{
	int i = sizeof(NoMementClass);

	int i1 = sizeof(ordClass);

	baseiv* p1 = new baseiv();
	p1->setName("123");

	baseiv_A* p2 = new baseiv_A();
	p2->setName("1235");
	p2->baseiv::setName("asss");
	delete p1;
	delete p2;


	{
		//以下是示例遮掩效果的处理，
		baseiv_A a;
		a.mf1();
		//a.mf1(5);	//wrong! 因为baseiv_A::mf1遮掩了Base::mf1
		a.mf2();
		a.mf3();
		a.mf3(5.0);	//加了using baseiv::mf3;的处理后才可见
	}
}
