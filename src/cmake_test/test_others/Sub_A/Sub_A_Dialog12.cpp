#include "Sub_A/Sub_A_Dialog12.h"
#include "ui_Sub_A_Dialog12.h"

Sub_A_Dialog12::Sub_A_Dialog12(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::Sub_A_Dialog12())
{
	m_pUI->setupUi(this);
}

Sub_A_Dialog12::~Sub_A_Dialog12()
{
	delete m_pUI;
	m_pUI = NULL;
}

