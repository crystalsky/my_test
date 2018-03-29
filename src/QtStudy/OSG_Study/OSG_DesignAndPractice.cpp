#include "OSG_DesignAndPractice.h"
#include "OSGViewTestWidget.h"
#include "QGroupBox"
#include "QGraphicsView"
#include "OSGProgramingGuid/T03.h"

OSG_DesignAndPractice::OSG_DesignAndPractice(QWidget* parent)
	: QWidget(parent)
{
	m_pTableWidget = new QTabWidget(this);
	QHBoxLayout* pLay = new QHBoxLayout(this);
	pLay->addWidget(m_pTableWidget);
}

OSG_DesignAndPractice::~OSG_DesignAndPractice()
{
	
}

