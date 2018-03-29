#include "boost_memory_manage.h"

namespace Study_Boost
{
	boost_memory_manage::boost_memory_manage( QWidget* pParent /*= NULL*/ )
	 : ReflectButtonFunctionWidget(pParent)
	{
		//TODO: add the reflection class name
		QStringList listFunc = QStringList() 
			<< "boost_pool";

		addFunctionButtons(listFunc);
	}

	bool boost_memory_manage::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (ReflectButtonFunctionWidget::onButtonClicked(strFunctionButtonName))
		{
			return true;
		}

		//TODO:


		return false;
	}
}
