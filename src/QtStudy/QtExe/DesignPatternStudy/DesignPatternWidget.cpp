#include "DesignPatternWidget.h"
#include "glog.h"
#include "LiskovSubstitutionPrinciple.h"

namespace DesignPattern
{
	DesignPatternWidget::DesignPatternWidget( QWidget* pParent /*= NULL*/ )
		: QtUI::CButtonFunctionWidget(4, pParent)
	{
		init();
	}

	void DesignPatternWidget::init()
	{
		QStringList listFunc = QStringList() <<
			"LiskovSubstitutionPrinciple(LSP)";


		addFunctionButtons(listFunc);
	}

	bool DesignPatternWidget::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (strFunctionButtonName == "LiskovSubstitutionPrinciple(LSP)")
		{
			LiskovSubstitutionPrinciple::run();
		}

		return true;
	}
}
