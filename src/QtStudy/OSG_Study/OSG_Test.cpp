#include "OSG_Test.h"
#include "ui_OSG_Test.h"

OSG_Test::OSG_Test(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::OSG_Test())
{
	m_pUI->setupUi(this);
}

OSG_Test::~OSG_Test()
{
	delete m_pUI;
	m_pUI = NULL;
}

