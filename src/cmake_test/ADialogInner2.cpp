#include "ADialogInner2.h"
#include "ui_ADialogInner2.h"

ADialogInner2::ADialogInner2(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::ADialogInner2())
{
	m_pUI->setupUi(this);
}

ADialogInner2::~ADialogInner2()
{
	delete m_pUI;
	m_pUI = NULL;
}

