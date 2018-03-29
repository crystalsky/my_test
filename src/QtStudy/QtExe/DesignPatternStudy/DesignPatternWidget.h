#ifndef DesignPatternWidget_h__
#define DesignPatternWidget_h__

#include "StepBase.h"

namespace DesignPattern
{
	class DesignPatternWidget : public QtUI::CButtonFunctionWidget
	{
		Q_OBJECT
	public:
		DesignPatternWidget(QWidget* pParent = NULL);
		~DesignPatternWidget(){}

	public:
		void init();

	protected Q_SLOTS:
		
	private:
		virtual bool onButtonClicked(const QString& strFunctionButtonName);
		
	private:
	};
}

#endif // DesignPatternWidget_h__
