#include "Page_QtWithCPP.h"
#include "QtProjectPath.h"
#include <QtConcurrent/QtConcurrent>
#include "qfuturewatcher.h"
#include "glog.h"
#include "type_classification.h"

namespace Study_QtCore
{
	CPage_QtWithCPP::CPage_QtWithCPP( QWidget* pParent /*= NULL*/ )
		: QtUI::CButtonFunctionWidget(4, pParent)
	{
		init();
	}

	void CPage_QtWithCPP::init()
	{
		QStringList listFunc = QStringList() <<
			"TypeClassification";


		addFunctionButtons(listFunc);
	}

	bool CPage_QtWithCPP::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (strFunctionButtonName == "TypeClassification")
		{
			_TypeClassification();
		}

		return true;
	}

	void CPage_QtWithCPP::_TypeClassification()
	{
		TypeInfo<int**> myIntPP;
		//1
		//typedef typename TypeInfo<int*>::bottomT bottomT;
		//2
		//typedef typename TypeInfo<int>::bottomT bottomT;



		//TypeInfo<T*>:: bastT=int* ->
		//
		

	}
}