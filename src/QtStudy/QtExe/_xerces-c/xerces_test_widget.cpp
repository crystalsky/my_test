#include "xerces_test_widget.h"

xerces_test_widget::xerces_test_widget( QWidget* pParnet )
	: QtUI::CStepBase(pParnet)
{
	addFunctionalWidget(QStringLiteral("xerces_test_widget_1"), 
		new xerces_test_widget_SubWidget(this));
}

xerces_test_widget::~xerces_test_widget()
{

}


xerces_test_widget_SubWidget::xerces_test_widget_SubWidget( QWidget* pParent /*= NULL*/ )
 : ReflectButtonFunctionWidget(pParent)
{
	//TODO: add the reflection class name
	QStringList listFunc = QStringList() 
		<< "xerces_dom_test";

	addFunctionButtons(listFunc);
}

bool xerces_test_widget_SubWidget::onButtonClicked( const QString& strFunctionButtonName )
{
	if (ReflectButtonFunctionWidget::onButtonClicked(strFunctionButtonName))
	{
		return true;
	}

	//TODO:


	return false;
}
