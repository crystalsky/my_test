#ifndef Page_QtConcurrent_h__
#define Page_QtConcurrent_h__

#include "StepBase.h"
#include <QRunnable>
#include <QEvent>
#include <QFutureWatcher>
#include <Quuid>
#include <QTime>
#include <QThread>
#include <QInputDialog>
#include <QProgressDialog>
#include <ConcurentRunnableManager.h>
#include <ConcurentRunnable.h>
namespace QtUtilityEx
{
	
}

namespace Study_QtCore
{
	class myRunnable : public QtUtility::ConcurentRunnable
	{
		Q_OBJECT
	public:
		myRunnable(QObject* pReciever, QString& strTaskName)
			: QtUtility::ConcurentRunnable(pReciever, strTaskName)
		{

		}

	private:
		void run()
		{
			QTime t;
			t.start();
			int n(0);
			double dVla = 0;
			for (int i = 0; i < 50000; ++i)
			{
				for (int j = 0; j < 20000; ++j)
				{
					dVla += pow(i, j);
				}
			}

			qDebug() << QThread::currentThreadId() <<"elapsed:" << t.elapsed();
		}
	};

	class CPage_QtConcurrent : public QtUI::CStepBase
	{
		Q_OBJECT
	public:
		CPage_QtConcurrent(QWidget* pParnet);
		~CPage_QtConcurrent();

	protected:
		void initFunctionWidgets();
	};

	class CWidget1 : public QtUI::CWidgetBase
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
		void slot_ConcurentRunnableManager();


		void slot_progressChanged(int nTotal, int nCur);
		void slot_runnerFinish();
	private:
		void addButton(int nRow, int nColume, const QString& strButtonName);
	private:
		void _QtConcurunt_mapped();
		void _QtConcurunt_map();
	private:
		QGridLayout*	m_pGridLayout;

		QtUtility::ConcurentRunnableManager* m_mgr;
		QProgressDialog* m_pQProgressDialog;
	};
}

#endif // Page_QtConcurrent_h__
