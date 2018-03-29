#include "AWidget.h"
#include "ui_AWidget.h"

AWidget::AWidget(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::AWidget())
{
	m_pUI->setupUi(this);
}

AWidget::~AWidget()
{
	delete m_pUI;
	m_pUI = NULL;
}

