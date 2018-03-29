#ifndef Page1_h__
#define Page1_h__

#include "../StepBase.h"

namespace Study_QtGui
{
	class CPage1 : public Study_BaseClass::CStepBase
	{
		Q_OBJECT
	public:
		CPage1(QWidget* pParnet);
		~CPage1();

	protected:
		void initFunctionWidgets();
	};
}

namespace Study_QtGui
{
	namespace Gui_Widget1
	{
		class CQMLTranslucentWidget : public QDialog
		{
		public:
			CQMLTranslucentWidget();

		protected:
			void paintEvent(QPaintEvent *painter);
		private:
			void init();
		};
	}
	
	class CWidget1 : public Study_BaseClass::CButtonFunctionWidget
	{
		Q_OBJECT
	public:
		CWidget1(QWidget* pParent = NULL);
		~CWidget1(){}

	public:
		void init();

	private:
		virtual bool onButtonClicked(const QString& strFunctionButtonName);
	};
}

#endif // Page1_h__
