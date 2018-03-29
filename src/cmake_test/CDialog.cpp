#include "CDialog.h"
#include "ui_CDialog.h"

CDialog::CDialog(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::CDialog())
{
	m_pUI->setupUi(this);
}

CDialog::~CDialog()
{
	delete m_pUI;
	m_pUI = NULL;
}

