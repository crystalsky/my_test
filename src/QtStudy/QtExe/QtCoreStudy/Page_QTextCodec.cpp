#include "Page_QTextCodec.h"

Page_QTextCodec::Page_QTextCodec( QWidget* pParnet )
	: QtUI::CStepBase(pParnet)
{
	addFunctionalWidget(QStringLiteral("Page_QTextCodec_SubWidget"), 
		new Page_QTextCodec_SubWidget(this));
}

Page_QTextCodec::~Page_QTextCodec()
{

}


Page_QTextCodec_SubWidget::Page_QTextCodec_SubWidget( QWidget* pParent /*= NULL*/ )
 : ReflectButtonFunctionWidget(pParent)
{
	//TODO: add the reflection class name
	QStringList listFunc = QStringList() 
		<< "1";

	addFunctionButtons(listFunc);
}

bool Page_QTextCodec_SubWidget::onButtonClicked( const QString& strFunctionButtonName )
{
	if (ReflectButtonFunctionWidget::onButtonClicked(strFunctionButtonName))
	{
		return true;
	}

	//TODO:


	return false;
}
