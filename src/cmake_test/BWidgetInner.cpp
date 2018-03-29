#include "BWidgetInner.h"
#include "ui_BWidgetInner.h"

BWidgetInner::BWidgetInner(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::BWidgetInner())
{
	m_pUI->setupUi(this);
}

BWidgetInner::~BWidgetInner()
{
	delete m_pUI;
	m_pUI = NULL;
}

