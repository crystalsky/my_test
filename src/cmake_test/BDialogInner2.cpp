#include "BDialogInner2.h"
#include "ui_BDialogInner2.h"

BDialogInner2::BDialogInner2(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::BDialogInner2())
{
	m_pUI->setupUi(this);
}

BDialogInner2::~BDialogInner2()
{
	delete m_pUI;
	m_pUI = NULL;
}

