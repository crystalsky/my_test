#include "CDialogInner2.h"
#include "ui_CDialogInner2.h"

CDialogInner2::CDialogInner2(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::CDialogInner2())
{
	m_pUI->setupUi(this);
}

CDialogInner2::~CDialogInner2()
{
	delete m_pUI;
	m_pUI = NULL;
}

