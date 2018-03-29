#include "CWidgetInner.h"
#include "ui_CWidgetInner.h"

CWidgetInner::CWidgetInner(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::CWidgetInner())
{
	m_pUI->setupUi(this);
}

CWidgetInner::~CWidgetInner()
{
	delete m_pUI;
	m_pUI = NULL;
}

