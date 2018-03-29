#include "AWidgetInner2.h"
#include "ui_AWidgetInner2.h"

AWidgetInner2::AWidgetInner2(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::AWidgetInner2())
{
	m_pUI->setupUi(this);
}

AWidgetInner2::~AWidgetInner2()
{
	delete m_pUI;
	m_pUI = NULL;
}

