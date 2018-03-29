#ifndef SattliteInfoTest_h__
#define SattliteInfoTest_h__

#include "QMLStudyBase.h"

namespace Study_QML
{
	class CSattliteInfoTest : public QtUI::CStepBase
	{
		Q_OBJECT
	public:
		CSattliteInfoTest(QWidget* pParnet);
		~CSattliteInfoTest();

	protected:
		void initFunctionWidgets();
	};

	namespace SattliteInfo
	{
		typedef CQMLWidgetBase CSattliteTimeCells;
		typedef CQMLWidgetBase SattliteTime;
	}
}

#endif // SattliteInfoTest_h__
