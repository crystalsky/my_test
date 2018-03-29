#ifndef boost_test_1_h__
#define boost_test_1_h__

#include "StepBase.h"
#include "ReflectButtonFunctionWidget.h"

namespace Study_Boost
{
	class boost_test_1 : public QtUI::CStepBase
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
	class CWidget1 : public QtUI::CButtonFunctionWidget
	{
		Q_OBJECT
	public:
		CWidget1(QWidget* pParent = NULL);
		~CWidget1(){}

	public:
		void init();
	private:
		virtual bool onButtonClicked(const QString& strFunctionButtonName);
	};
}

namespace Study_Boost
{
	class boost_func_test : public ReflectButtonFunctionWidget
	{
		Q_OBJECT
	public:
		boost_func_test(QWidget* pParent = NULL);
		~boost_func_test(){}

	public:
		void init();
	private:
		virtual bool onButtonClicked(const QString& strFunctionButtonName);
	};
}

#endif // boost_test_1_h__
