#include "ADialog.h"
#include "ui_ADialog.h"

ADialog::ADialog(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::ADialog())
{
	m_pUI->setupUi(this);
}

ADialog::~ADialog()
{
	delete m_pUI;
	m_pUI = NULL;
}

