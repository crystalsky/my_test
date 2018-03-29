#include "CDialogInner.h"
#include "ui_CDialogInner.h"

CDialogInner::CDialogInner(QDialog* parent)
	: QDialog(parent)
	, m_pUI(new Ui::CDialogInner())
{
	m_pUI->setupUi(this);
}

CDialogInner::~CDialogInner()
{
	delete m_pUI;
	m_pUI = NULL;
}

