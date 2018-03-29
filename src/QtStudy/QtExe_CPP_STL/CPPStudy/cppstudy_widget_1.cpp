#include "cppstudy_widget_1.h"

namespace cppstudy
{
	cppstudy_widget_1::cppstudy_widget_1( QWidget* pParent /*= NULL*/ )
	 : ReflectButtonFunctionWidget(pParent)
	{
		//TODO: add the reflection class name
		QStringList listFunc = QStringList() 
			<< "classoverride"
			<< "Non_Virtual_Interface"
			<< "Strategy_By_FunctionPointer"
			<< "Strategy_By_TR1_Function";

		addFunctionButtons(listFunc);
	}

	bool cppstudy_widget_1::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (ReflectButtonFunctionWidget::onButtonClicked(strFunctionButtonName))
		{
			return true;
		}

		//TODO:


		return false;
	}
}
