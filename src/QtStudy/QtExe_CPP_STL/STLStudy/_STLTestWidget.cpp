#include "_STLTestWidget.h"
#include "inc_stl.h"
#include "qt_includes.h"

_STLTestWidget::_STLTestWidget( QWidget* pParnet )
	: QtUI::CStepBase(pParnet)
{
	addFunctionalWidget(QStringLiteral("_STLTestWidget_SubWidget"), 
		new _STLTestWidget_SubWidget(this));
}

_STLTestWidget::~_STLTestWidget()
{

}


_STLTestWidget_SubWidget::_STLTestWidget_SubWidget( QWidget* pParent /*= NULL*/ )
 : ReflectButtonFunctionWidget(pParent)
{
	//TODO: add the reflection class name
	QStringList listFunc = QStringList() 
		<< "ContainerTest"
		<< "vector_erease"
		<< "std_copy"
		<< "std_for_each"
		<< "std_transform"
		<< "std_unary_function"
		<< "std_with_lambda"

		;

	addFunctionButtons(listFunc);
}

bool _STLTestWidget_SubWidget::onButtonClicked( const QString& strFunctionButtonName )
{
	if (ReflectButtonFunctionWidget::onButtonClicked(strFunctionButtonName))
	{
		return true;
	}

	//TODO:


	return false;
}
