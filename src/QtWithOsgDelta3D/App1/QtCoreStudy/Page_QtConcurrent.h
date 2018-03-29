#ifndef Page_QtConcurrent_h__
#define Page_QtConcurrent_h__

#include "../StepBase.h"

namespace Study_QtCore
{
	class CPage_QtConcurrent : public Study_BaseClass::CStepBase
	{
		Q_OBJECT
	public:
		CPage_QtConcurrent(QWidget* pParnet);
		~CPage_QtConcurrent();

	protected:
		void initFunctionWidgets();
	};

	class CWidget1 : public Study_BaseClass::CWidgetBase
	{
		Q_OBJECT
	public:
		CWidget1(QWidget* pParent = NULL);
		~CWidget1(){}

	public:
		void init();

	protected Q_SLOTS:
		void slotClicked();
		void slot_QtConcurunt_map_finished();
		void slot_QtConcurunt_map_progressValueChanged(int progressValue);
		void slot_QtConcurunt_mapped_finished();
		void slot_QtConcurunt_mapped_progressValueChanged(int progressValue);
		void slot_QtConcurunt_mapped_resultReadyAt(int progressValue);
		void slot_QtConcurunt_mapped_progressRangeChanged(int minn, int maxn);
	private:
		void addButton(int nRow, int nColume, const QString& strButtonName);
	private:
		void _QtConcurunt_mapped();
		void _QtConcurunt_map();
	private:
		QGridLayout*	m_pGridLayout;
	};
}

#endif // Page_QtConcurrent_h__
