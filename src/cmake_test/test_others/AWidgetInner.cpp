#include "AWidgetInner.h"
#include "ui_AWidgetInner.h"

AWidgetInner::AWidgetInner(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::AWidgetInner())
{
	m_pUI->setupUi(this);
}

AWidgetInner::~AWidgetInner()
{
	delete m_pUI;
	m_pUI = NULL;
}

