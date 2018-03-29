#ifndef Step1_h__
#define Step1_h__

#include "QMLStudyBase.h"

namespace Study_QML
{
	class CStep1 : public Study_BaseClass::CStepBase
	{
		Q_OBJECT
	public:
		CStep1(QWidget* pParnet);
		~CStep1();

	protected:
		void initFunctionWidgets();
	};

	class chapter1_basics_piechart : public Study_BaseClass::CWidgetBase
	{
		Q_OBJECT
	public:
		chapter1_basics_piechart(QWidget* pParent = NULL);
		~chapter1_basics_piechart();

		virtual void refresh();

	private:
		QWidget*	m_pQuitWidget;
		QVBoxLayout* m_pLay;
	};

	class CQMLSceneWidget_BaseTest : public CQMLSceneWidget
	{
	public:
		CQMLSceneWidget_BaseTest(QWidget* pParent = NULL);

	protected:
		void init();

		virtual bool onButtonClicked(const QString& strFunctionButtonName);
	};

	class CQMLSceneWidget_Animation : public CQMLSceneWidget
	{
	public:
		CQMLSceneWidget_Animation(QWidget* pParent = NULL);

	protected:
		void init();

		virtual bool onButtonClicked(const QString& strFunctionButtonName);
	};
}

#endif // Step1_h__
