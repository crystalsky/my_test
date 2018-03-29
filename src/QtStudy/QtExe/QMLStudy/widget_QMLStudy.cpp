#include "widget_QMLStudy.h"
#include "Step1.h"
#include "SattliteInfoTest.h"

CWidget_QMLStudy::CWidget_QMLStudy( QWidget* pParent /*= NULL*/ )
{
	m_binit = false;

	try
	{
		test1();
	}
	catch(const std::runtime_error& e)
	{

	}
}

CWidget_QMLStudy::~CWidget_QMLStudy()
{

}

void CWidget_QMLStudy::init()
{
	m_pTabWidget = new QTabWidget(this);
	//m_pTabWidget->setTabPosition(QTabWidget::West);
	QVBoxLayout* pLay = new QVBoxLayout;
	pLay->addWidget(m_pTabWidget);
	setLayout(pLay);

	m_pTabWidget->addTab(new Study_QML::CStep1(this), 
		QStringLiteral("Step_1"));
	m_pTabWidget->addTab(new Study_QML::CSattliteInfoTest(this), 
		QStringLiteral("SattliteInfoTest"));
	
}

void CWidget_QMLStudy::showEvent( QShowEvent *e )
{
	if (!m_binit)
	{
		init();
		m_binit = true;
	}
	QWidget::showEvent(e);
}

void CWidget_QMLStudy::test1() throw(std::runtime_error)
{
	throw std::runtime_error("adsfadf");
}