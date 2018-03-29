#include "AWidget2.h"
#include "ui_AWidget2.h"

AWidget2::AWidget2(QWidget* parent)
	: QWidget(parent)
	, m_pUI(new Ui::AWidget2())
{
	m_pUI->setupUi(this);
}

AWidget2::~AWidget2()
{
	delete m_pUI;
	m_pUI = NULL;
}

