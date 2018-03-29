#include "OSGViewTestWidget.h"
#include "ui_OSGViewTestWidget.h"
#include "osgviewerQt.h"


OSGViewTestWidget::OSGViewTestWidget(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::OSGViewTestWidget())
{
	m_pUI->setupUi(this);
	m_pViewerWidget = new ViewerWidget;

	QVBoxLayout* pLay = new QVBoxLayout(m_pUI->groupBoxOsgViewer);
	pLay->setContentsMargins(0, 0, 0, 0);
	pLay->addWidget(m_pViewerWidget);

	connect(m_pUI->pushButtonChangeOSGNodeFile, SIGNAL(clicked()), SLOT(slotChangeOSgFile()));
	connect(m_pUI->pushButtonPathLineRectTest, SIGNAL(clicked()), SLOT(slotPathLineRect()));
}

OSGViewTestWidget::~OSGViewTestWidget()
{
	delete m_pUI;
	m_pUI = NULL;
}

void OSGViewTestWidget::slotChangeOSgFile()
{
	static int aFileIndex = 0;

	if (aFileIndex == 0)
	{
		m_pViewerWidget->setSceneData(osgDB::readNodeFile("glider.osgt"));
	}
	else if (aFileIndex == 1)
	{
		m_pViewerWidget->setSceneData(osgDB::readNodeFile("axes.osgt"));
	}
	else if (aFileIndex == 2)
	{
		m_pViewerWidget->setSceneData(osgDB::readNodeFile("fountain.osgt"));
	}
	else
	{
		m_pViewerWidget->setSceneData(osgDB::readNodeFile("cow.osgt"));
		aFileIndex = -1;
	}

	aFileIndex++;
	
}

void OSGViewTestWidget::slotPathLineRect()
{
	
}