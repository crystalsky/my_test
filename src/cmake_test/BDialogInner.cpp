#include "BDialogInner.h"
#include "ui_BDialogInner.h"

BDialogInner::BDialogInner(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::BDialogInner())
{
	m_pUI->setupUi(this);
}

BDialogInner::~BDialogInner()
{
	delete m_pUI;
	m_pUI = NULL;
}

