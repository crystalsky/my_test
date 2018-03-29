#include "OSG_Examples.h"
#include "ui_OSG_Examples.h"

OSG_Examples::OSG_Examples(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::OSG_Examples())
{
	m_pUI->setupUi(this);
}

OSG_Examples::~OSG_Examples()
{
	delete m_pUI;
	m_pUI = NULL;
}

