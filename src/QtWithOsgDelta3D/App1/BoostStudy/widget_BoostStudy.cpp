#include "widget_BoostStudy.h"
#include "boost_test_1.h"
namespace Study_Boost{
CWidget_BoostStudy::CWidget_BoostStudy( QWidget* pParent /*= NULL*/ )
{
	init();
}

void CWidget_BoostStudy::init()
{
	m_pTabWidget = new QTabWidget(this);
	//m_pTabWidget->setTabPosition(QTabWidget::West);
	QVBoxLayout* pLay = new QVBoxLayout;
	pLay->addWidget(m_pTabWidget);
	setLayout(pLay);

	m_pTabWidget->addTab(new Study_Boost::boost_test_1(this), QStringLiteral("boost_test_1"));
}
}