#include "boost_test_1.h"
#include "QtProjectPath.h"
//#include "_timer.h"
#include "_signals.h"
#include "_exception.h"
#include "_tuple.h"
#include "_lexical_cast.h"
#include "_circle_buffer.h"
#include "boost_func_test.h"

namespace Study_Boost
{
	boost_test_1::boost_test_1( QWidget* pParnet )
		: QtUI::CStepBase(pParnet)
	{
		initFunctionWidgets();
	}

	boost_test_1::~boost_test_1()
	{

	}

	void boost_test_1::initFunctionWidgets()
	{
		addFunctionalWidget(QStringLiteral("boost_func_test"), 
			new Study_Boost::boost_func_test(this));
		addFunctionalWidget(QStringLiteral("Base_Info"), 
			new Study_Boost::CWidget1(this));
	}
}

namespace Study_Boost
{
	CWidget1::CWidget1( QWidget* pParent /*= NULL*/ ) : CButtonFunctionWidget(pParent)
	{
		init();
	}

	void CWidget1::init()
	{
		addFunctionButton(QStringLiteral("boost_time"));
		addFunctionButton(QStringLiteral("boost_signals"));
		addFunctionButton(QStringLiteral("boost_exception"));
		addFunctionButton(QStringLiteral("boost_tuple"));
		addFunctionButton(QStringLiteral("boost_lexical_cast"));
		addFunctionButton(QStringLiteral("boost_pool"));
		addFunctionButton(QStringLiteral("boost_base64"));
	}

	bool CWidget1::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (strFunctionButtonName == QStringLiteral("boost_time"))
		{
			//boost_timer::GetInstance()->runTest();
		}
		else if (strFunctionButtonName == QStringLiteral("boost_signals"))
		{
			boost_signasl::GetInstance()->runTest();
		}
		else if ("boost_exception" == strFunctionButtonName)
		{
			boost_exception::GetInstance()->runTest();
		}
		else if ("boost_tuple" == strFunctionButtonName)
		{
			boost_tuple::GetInstance()->runTest();
		}
		else if ("boost_lexical_cast" == strFunctionButtonName)
		{
			boost_lexical_cast::GetInstance()->runTest();
		}
		else if ("boost_pool" == strFunctionButtonName)
		{

		}
		else if ("boost_base64" == strFunctionButtonName)
		{

		}

		return true;
	}
}


namespace Study_Boost
{
	boost_func_test::boost_func_test( QWidget* pParent /*= NULL*/ )
		: ReflectButtonFunctionWidget(pParent)
	{
		//TODO: add the reflection class name
		QStringList listFunc = QStringList() 
			<< "_base64"
			<< "boost_ptree_xml" 
			<< "_circle_buffer";


		addFunctionButtons(listFunc);
	}

	bool boost_func_test::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (ReflectButtonFunctionWidget::onButtonClicked(strFunctionButtonName))
		{
			return true;
		}

		//TODO:


		return false;
	}
}
