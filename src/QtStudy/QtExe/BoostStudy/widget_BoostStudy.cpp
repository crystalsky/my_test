#include "widget_BoostStudy.h"
#include "boost_test_1.h"
#include "boost_memory_manage.h"
#include "boost_func_test.h"

namespace Study_Boost
{
	CWidget_BoostStudy::CWidget_BoostStudy( QWidget* pParent /*= NULL*/ )
	{
		init();
	}

	void CWidget_BoostStudy::init()
	{
		m_pTabWidget = new QTabWidget(this);
		QVBoxLayout* pLay = new QVBoxLayout;
		pLay->addWidget(m_pTabWidget);
		setLayout(pLay);

		m_pTabWidget->addTab(new Study_Boost::boost_test_1(this), 
			QStringLiteral("boost_test_1"));
		m_pTabWidget->addTab(new Study_Boost::boost_memory_manage(this), 
			QStringLiteral("boost_memory_manage"));
	}

}