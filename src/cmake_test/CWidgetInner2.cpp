#include "CWidgetInner2.h"
#include "ui_CWidgetInner2.h"

CWidgetInner2::CWidgetInner2(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::CWidgetInner2())
{
	m_pUI->setupUi(this);
}

CWidgetInner2::~CWidgetInner2()
{
	delete m_pUI;
	m_pUI = NULL;
}

