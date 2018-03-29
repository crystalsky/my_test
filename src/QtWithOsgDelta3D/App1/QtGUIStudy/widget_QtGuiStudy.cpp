#include "widget_QtGuiStudy.h"
#include "Page1.h"

CWidget_QMLGui::CWidget_QMLGui( QWidget* pParent /*= NULL*/ )
{
	init();
}

CWidget_QMLGui::~CWidget_QMLGui()
{

}

void CWidget_QMLGui::init()
{
	m_pTabWidget = new QTabWidget(this);
	//m_pTabWidget->setTabPosition(QTabWidget::West);
	QVBoxLayout* pLay = new QVBoxLayout;
	pLay->addWidget(m_pTabWidget);
	setLayout(pLay);

	m_pTabWidget->addTab(new Study_QtGui::CPage1(this), QStringLiteral("Page_1"));
	//m_pTabWidget->addTab(new Study_QML::CStep1(this), QStringLiteral("Step1"));
}