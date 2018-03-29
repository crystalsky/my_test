#include "template_test_widget.h"
#include "template_test_1.h"
template_test_widget::template_test_widget( QWidget* pParnet )
	: QtUI::CStepBase(pParnet)
{
	addFunctionalWidget(QStringLiteral("template_test_widget_SubWidget"), 
		new template_test_widget_SubWidget(this));
}

template_test_widget::~template_test_widget()
{

}


template_test_widget_SubWidget::template_test_widget_SubWidget( QWidget* pParent /*= NULL*/ )
 : ReflectButtonFunctionWidget(pParent)
{
	//TODO: add the reflection class name
	QStringList listFunc = QStringList() 
		<< "template_test_1";

	addFunctionButtons(listFunc);
}

bool template_test_widget_SubWidget::onButtonClicked( const QString& strFunctionButtonName )
{
	if (ReflectButtonFunctionWidget::onButtonClicked(strFunctionButtonName))
	{
		return true;
	}

	//TODO:


	return false;
}
