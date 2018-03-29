#include "BDialog.h"
#include "ui_BDialog.h"

BDialog::BDialog(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::BDialog())
{
	m_pUI->setupUi(this);
}

BDialog::~BDialog()
{
	delete m_pUI;
	m_pUI = NULL;
}

