#include "widget_QtCoreStudy.h"
#include "Page_QtConcurrent.h"

namespace Study_QtCore
{
	CStudyWidget::CStudyWidget( QWidget* pParent /*= NULL*/ )
	{
		init();
	}

	CStudyWidget::~CStudyWidget()
	{

	}

	void CStudyWidget::init()
	{
		m_pTabWidget = new QTabWidget(this);
		QVBoxLayout* pLay = new QVBoxLayout;
		pLay->addWidget(m_pTabWidget);
		setLayout(pLay);

		m_pTabWidget->addTab(new Study_QtCore::CPage_QtConcurrent(this), 
			QStringLiteral("QtConcurrent"));
	}
}
