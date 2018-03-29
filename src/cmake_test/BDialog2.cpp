#include "BDialog2.h"
#include "ui_BDialog2.h"

BDialog2::BDialog2(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::BDialog2())
{
	m_pUI->setupUi(this);
}

BDialog2::~BDialog2()
{
	delete m_pUI;
	m_pUI = NULL;
}

