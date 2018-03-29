#include "ADialog2.h"
#include "ui_ADialog2.h"

ADialog2::ADialog2(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::ADialog2())
{
	m_pUI->setupUi(this);
}

ADialog2::~ADialog2()
{
	delete m_pUI;
	m_pUI = NULL;
}

