#include "ReflectButtonFunctionWidget.h"
#include "Base.h"
#include <glog.h>

ReflectButtonFunctionWidget::ReflectButtonFunctionWidget( QWidget* pParent /*= NULL*/ )
	: CButtonFunctionWidget(pParent)
{
	
}

ReflectButtonFunctionWidget::ReflectButtonFunctionWidget( int nColNum, QWidget* pParent /*= NULL*/ )
	: CButtonFunctionWidget(nColNum, pParent)
{

}

bool ReflectButtonFunctionWidget::onButtonClicked( const QString& strFunctionButtonName )
{
	QScopedPointer<my_kit::base> pObj(
		UtilityKit::createTypeObject<my_kit::base>(
		strFunctionButtonName.toLocal8Bit().data()));

	if (pObj.isNull())
	{
		LOG(ERROR) << "No Default Reflect class To resolve the Function [" 
			<< strFunctionButtonName.toLocal8Bit().data();
		return false;
	}

	pObj->run();

	return true;
}
