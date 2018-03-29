#include "Sub_A_DialogInner_12.h"
#include "ui_Sub_A_DialogInner_12.h"

Sub_A_DialogInner_12::Sub_A_DialogInner_12(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::Sub_A_DialogInner_12())
{
	m_pUI->setupUi(this);
}

Sub_A_DialogInner_12::~Sub_A_DialogInner_12()
{
	delete m_pUI;
	m_pUI = NULL;
}

