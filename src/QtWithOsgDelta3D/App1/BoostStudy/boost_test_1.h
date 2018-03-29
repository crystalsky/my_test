#ifndef boost_test_1_h__
#define boost_test_1_h__

#include "../StepBase.h"

namespace Study_Boost
{
	class boost_test_1 : public Study_BaseClass::CStepBase
	{
		Q_OBJECT
	public:
		boost_test_1(QWidget* pParnet);
		~boost_test_1();

	protected:
		void initFunctionWidgets();
	};
}

namespace Study_Boost
{
	class CWidget1 : public Study_BaseClass::CButtonFunctionWidget
	{
		Q_OBJECT
	public:
		CWidget1(QWidget* pParent = NULL);
		~CWidget1(){}

	public:
		void init();
	private:
		virtual bool onButtonClicek(const QString& strFunctionButtonName);
	};
}

#endif // boost_test_1_h__
