#include "ADialogInner.h"
#include "ui_ADialogInner.h"

ADialogInner::ADialogInner(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::ADialogInner())
{
	m_pUI->setupUi(this);
}

ADialogInner::~ADialogInner()
{
	delete m_pUI;
	m_pUI = NULL;
}

