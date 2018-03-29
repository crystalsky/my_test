#include "CWidget.h"
#include "ui_CWidget.h"

CWidget::CWidget(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::CWidget())
{
	m_pUI->setupUi(this);
}

CWidget::~CWidget()
{
	delete m_pUI;
	m_pUI = NULL;
}

