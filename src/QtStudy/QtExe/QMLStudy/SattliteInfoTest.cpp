#include "SattliteInfoTest.h"

namespace Study_QML
{
	CSattliteInfoTest::CSattliteInfoTest( QWidget* pParnet )
		: QtUI::CStepBase(pParnet)
	{
		initFunctionWidgets();
	}

	CSattliteInfoTest::~CSattliteInfoTest()
	{

	}

	void CSattliteInfoTest::initFunctionWidgets()
	{
		addFunctionalWidget(QStringLiteral("1_SattliteTimeCells"), 
			new SattliteInfo::CSattliteTimeCells("SattliteTimeCells.qml", this));

		addFunctionalWidget(QStringLiteral("2_SattliteTime"), 
			new SattliteInfo::SattliteTime("SattliteTime.qml", this));

		addFunctionalWidget(QStringLiteral("3_Service"), 
			new SattliteInfo::SattliteTime("SattliteTime.qml", this));

		addFunctionalWidget(QStringLiteral("4_Information"), 
			new SattliteInfo::SattliteTime("SattliteTime.qml", this));

		addFunctionalWidget(QStringLiteral("5_IntegrationAll"), 
			new SattliteInfo::SattliteTime("SattliteAll.qml", this));
	}
}
