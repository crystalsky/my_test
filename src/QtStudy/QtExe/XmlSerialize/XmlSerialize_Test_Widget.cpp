#include "XmlSerialize_Test_Widget.h"

XmlSerialize_Test_Widget::XmlSerialize_Test_Widget( QWidget* pParnet )
	: QtUI::CStepBase(pParnet)
{
	addFunctionalWidget(QStringLiteral("XmlSerialize_Test_Widget_SubWidget"), 
		new XmlSerialize_Test_Widget_SubWidget(this));
}

XmlSerialize_Test_Widget::~XmlSerialize_Test_Widget()
{

}


XmlSerialize_Test_Widget_SubWidget::XmlSerialize_Test_Widget_SubWidget( QWidget* pParent /*= NULL*/ )
 : ReflectButtonFunctionWidget(pParent)
{
	//TODO: add the reflection class name
	QStringList listFunc = QStringList() 
		<< "XmlSerialize_Base_Test";

	addFunctionButtons(listFunc);
}

bool XmlSerialize_Test_Widget_SubWidget::onButtonClicked( const QString& strFunctionButtonName )
{
	if (ReflectButtonFunctionWidget::onButtonClicked(strFunctionButtonName))
	{
		return true;
	}

	//TODO:


	return false;
}
