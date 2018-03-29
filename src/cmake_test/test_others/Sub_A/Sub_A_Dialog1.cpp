#include "Sub_A/Sub_A_Dialog1.h"
#include "ui_Sub_A_Dialog1.h"

Sub_A_Dialog1::Sub_A_Dialog1(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::Sub_A_Dialog1())
{
	m_pUI->setupUi(this);
}

Sub_A_Dialog1::~Sub_A_Dialog1()
{
	delete m_pUI;
	m_pUI = NULL;
}

