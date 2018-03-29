#include "CWidget2.h"
#include "ui_CWidget2.h"

CWidget2::CWidget2(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::CWidget2())
{
	m_pUI->setupUi(this);
}

CWidget2::~CWidget2()
{
	delete m_pUI;
	m_pUI = NULL;
}

