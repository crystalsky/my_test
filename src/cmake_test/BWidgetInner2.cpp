#include "BWidgetInner2.h"
#include "ui_BWidgetInner2.h"

BWidgetInner2::BWidgetInner2(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::BWidgetInner2())
{
	m_pUI->setupUi(this);
}

BWidgetInner2::~BWidgetInner2()
{
	delete m_pUI;
	m_pUI = NULL;
}

