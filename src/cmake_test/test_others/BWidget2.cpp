#include "BWidget2.h"
#include "ui_BWidget2.h"

BWidget2::BWidget2(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::BWidget2())
{
	m_pUI->setupUi(this);
}

BWidget2::~BWidget2()
{
	delete m_pUI;
	m_pUI = NULL;
}

