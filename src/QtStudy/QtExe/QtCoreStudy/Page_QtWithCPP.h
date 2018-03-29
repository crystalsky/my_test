#ifndef Page_QtWithCPP_h__
#define Page_QtWithCPP_h__

#include "StepBase.h"

namespace Study_QtCore
{
	class CPage_QtWithCPP : public QtUI::CButtonFunctionWidget
	{
		Q_OBJECT
	public:
		CPage_QtWithCPP(QWidget* pParent = NULL);
		~CPage_QtWithCPP(){}

	public:
		void init();

	protected Q_SLOTS:
		
	private:
		virtual bool onButtonClicked(const QString& strFunctionButtonName);
		
	private:
		void _TypeClassification();
	};
}

#endif // Page_QtWithCPP_h__
