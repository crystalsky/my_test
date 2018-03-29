#include "Sub_A_DialogInner_1.h"
#include "ui_Sub_A_DialogInner_1.h"

Sub_A_DialogInner_1::Sub_A_DialogInner_1(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::Sub_A_DialogInner_1())
{
	m_pUI->setupUi(this);
}

Sub_A_DialogInner_1::~Sub_A_DialogInner_1()
{
	delete m_pUI;
	m_pUI = NULL;
}

