#include "Non_Virtual_Interface.h"
#include <memory>

//! NVI ����ʵ�� Template Method Pattern
namespace NVI
{
	class GameCharacter
	{
	public:
		GameCharacter(){}
		virtual ~GameCharacter(){}
	public:
		int getHealthValue()const			//derived classes no need to redefine it;
		{
			//TODO							... do something before like :loking a mutex/log entry/check constraint condition
			int nVal = doGetHealthValue();	//do realthing
			//TODO							...do something after: unlocking a mutex/log exit/check function condition after do realthing/check constarint condition again

			return nVal;
		}
		
	private:
		virtual int doGetHealthValue()const	 //! NVI �ַ������������д�ĺ��������⺯��������protect������ʱ��������ã�ֻ�л����ܾ�����ʱ���á���ô�������������Ȩ��
		{
			std::cout << "GameCharacter::doGetHealthValue";
			return 100;
		}
	};
	
	class GamePlayer1 : public GameCharacter
	{
	public:
		GamePlayer1(){}
		virtual ~GamePlayer1(){}
	private:
		virtual int doGetHealthValue()const	 //! NVI �ַ������������д�ĺ��������⺯��������protect������ʱ��������ã�ֻ�л����ܾ�����ʱ���á���ô�������������Ȩ��
		{
			std::cout << "GamePlayer1::doGetHealthValue";
			return 50;
		}
	};
}

IMPLEMENT_REFLECTED_CLASS(Non_Virtual_Interface)
Non_Virtual_Interface::Non_Virtual_Interface()
{
	
}

Non_Virtual_Interface::~Non_Virtual_Interface()
{
	
}

void Non_Virtual_Interface::run()
{
	std::tr1::shared_ptr<NVI::GameCharacter> player(new NVI::GamePlayer1());
	int nRet = player->getHealthValue();
}
