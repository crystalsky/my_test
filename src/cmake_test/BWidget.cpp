#include "BWidget.h"
#include "ui_BWidget.h"

BWidget::BWidget(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::BWidget())
{
	m_pUI->setupUi(this);
}

BWidget::~BWidget()
{
	delete m_pUI;
	m_pUI = NULL;
}

