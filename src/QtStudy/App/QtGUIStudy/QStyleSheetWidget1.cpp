#include "QStyleSheetWidget1.h"
#include "ui_QStyleSheetWidget1.h"

QStyleSheetWidget1::QStyleSheetWidget1(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::QStyleSheetWidget1())
{
	m_pUI->setupUi(this);
}

QStyleSheetWidget1::~QStyleSheetWidget1()
{
	delete m_pUI;
	m_pUI = NULL;
}

