#include "CDialog2.h"
#include "ui_CDialog2.h"

CDialog2::CDialog2(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::CDialog2())
{
	m_pUI->setupUi(this);
}

CDialog2::~CDialog2()
{
	delete m_pUI;
	m_pUI = NULL;
}

