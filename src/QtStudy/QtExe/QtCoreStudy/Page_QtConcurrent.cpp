#include "Page_QtConcurrent.h"
#include "QtProjectPath.h"
#include <QtConcurrent/QtConcurrent>
#include "qfuturewatcher.h"
#include "glog.h"

namespace QtUtilityEx
{

}

namespace Study_QtCore
{
	CPage_QtConcurrent::CPage_QtConcurrent( QWidget* pParnet )
		: QtUI::CStepBase(pParnet)
	{
		initFunctionWidgets();

		

	}

	CPage_QtConcurrent::~CPage_QtConcurrent()
	{

	}

	void CPage_QtConcurrent::initFunctionWidgets()
	{
		addFunctionalWidget(QStringLiteral("测试窗体_1"), 
			new CWidget1(this));
	}

	CWidget1::CWidget1( QWidget* pParent /*= NULL*/ )
	{
		init();

		m_pQProgressDialog = new QProgressDialog(this);
		m_pQProgressDialog->setAutoReset(false);
		m_pQProgressDialog->setAutoClose(false);

		m_mgr = new QtUtility::ConcurentRunnableManager(this);
		connect(m_mgr, SIGNAL(updateProgress(int, int)), this, SLOT(slot_progressChanged(int ,int)));
	}

	void CWidget1::init()
	{
		m_pGridLayout = new QGridLayout;
		setLayout(m_pGridLayout);

		addButton(0, 0, QStringLiteral("QtConcurunt::mapped"));
		addButton(0, 1, QStringLiteral("QtConcurunt::map"));
		addButton(0, 2, QStringLiteral("QtConcurunt::mapped Object"));
		addButton(1, 0, QStringLiteral("ConcurentRunnableManager"));
	}

	void CWidget1::addButton( int nRow, int nColume, const QString& strButtonName )
	{
		QPushButton* pButton = new QPushButton(strButtonName, this);
		pButton->setObjectName(strButtonName);
		connect(pButton, SIGNAL(clicked()), SLOT(slotClicked()));

		m_pGridLayout->addWidget(pButton, nRow, nColume);
	}

	void CWidget1::slotClicked()
	{
		QPushButton* pbutton = qobject_cast<QPushButton*>(sender());
		if (pbutton->objectName() == QStringLiteral("QtConcurunt::map"))
		{
			_QtConcurunt_map();
		}
		else if (pbutton->objectName() == QStringLiteral("QtConcurunt::mapped"))
		{
			_QtConcurunt_mapped();
		}
		else if (pbutton->objectName() == QStringLiteral("QtConcurunt::mapped Object"))
		{

		}
		else if (pbutton->objectName() == QStringLiteral("ConcurentRunnableManager"))
		{
			slot_ConcurentRunnableManager();
		}
	}

	void calc1(int &idex)
	{
		QTime t;
		t.start();
		static int nf = 0;
		for (int i = 0; i < 10000; ++i)
		{
			for (int j = 0; j < 10000; ++j)
			{
				//idex ++;
			}
		}
		
		qDebug() << QThread::currentThreadId() <<"elapsed:" << t.elapsed();
	}

	
	void CWidget1::_QtConcurunt_map()
	{
		QList<int> listCalc;
		for (int i = 0; i < 500; ++i)
		{
			listCalc << i + 1;
		}

		static QFutureWatcher<void> w1;
		w1.setFuture(QtConcurrent::map(listCalc, calc1));

		connect(&w1, SIGNAL(finished()), SLOT(slot_QtConcurunt_map_finished()));
		connect(&w1, SIGNAL(progressValueChanged(int)), 
			SLOT(slot_QtConcurunt_map_progressValueChanged(int)));
	}

	void CWidget1::slot_QtConcurunt_map_finished()
	{
		qDebug() << "slot_QtConcurunt_map_finished";
	}

	void CWidget1::slot_QtConcurunt_map_progressValueChanged( int progressValue )
	{
		qDebug() << progressValue;
	}

	void CWidget1::slot_ConcurentRunnableManager()
	{
		int nThreadCount = QInputDialog::getInt(this, "ThreadNum", "Num:", 10, 10, 10000, 10);

		QList<QtUtility::ConcurentRunnable*> listrun;
		for (int i = 0; i < nThreadCount; ++i)
		{
			QtUtility::ConcurentRunnable* pr = 
				new myRunnable(this, QString("CalcTest:%1").arg(i+1));
			connect(pr, SIGNAL(finished()), this, SLOT(slot_runnerFinish()));
			listrun << pr;
		}

		m_mgr->addProcessRunnable(listrun);
	}

	void CWidget1::slot_runnerFinish()
	{
		myRunnable* pr = qobject_cast<myRunnable*>(sender());

		if (pr)
		{
		}
	}

	void CWidget1::slot_progressChanged( int nTotal, int nCur )
	{
		if (nTotal == 0)
		{
			return;
		}
		m_pQProgressDialog->setRange(0, nTotal);
		m_pQProgressDialog->setValue(nCur);
		m_pQProgressDialog->show();
	}

	typedef struct stEMDataInfo
	{
		/////////////////////////
		//结构体变量
		int *	_arrColor;
		int nsize;
		/////////////////////////
		stEMDataInfo()
		{
			init();
		}

		~stEMDataInfo()
		{
			release();
		}

		stEMDataInfo(const stEMDataInfo& src)
		{
			init();
			*this = src;
		}

		stEMDataInfo& operator=(const stEMDataInfo& src)
		{
			if(this != &src)
			{
				release();

				//赋值
				nsize = src.nsize;
				if (src.nsize && src._arrColor != NULL)
				{
					_arrColor = new int[src.nsize];
					memcpy(_arrColor, src._arrColor, sizeof(int) * sizeof(int));
				}
			}
			return *this;
		}

		//初始化
		void init()
		{
			//赋值
			nsize = 0;
			_arrColor = NULL;
		}

		//析构
		void release()
		{
			if (nsize && _arrColor)
			{
				delete _arrColor;
				_arrColor = NULL;
			}
		}
	}EMDataInfo;

	stEMDataInfo* calc2(const int& idex)
	{
		QTime t;
		t.start();
		static int nf = 0;

		stEMDataInfo * result = new stEMDataInfo;
		int nrow = 1000;
		int nCol = 10000;
		result->nsize = nrow * nCol;
		result->_arrColor = new int[result->nsize];
		for (int i = 0; i < nrow; ++i)
		{
			for (int j = 0; j < nCol; ++j)
			{
				result->_arrColor[i * nrow + j] = nrow * idex;
			}
		}

		qDebug() << QThread::currentThreadId() <<"elapsed:" << t.elapsed();

		return result;
	}

	QFutureWatcher<stEMDataInfo*> w2;
	void CWidget1::_QtConcurunt_mapped()
	{
		qDebug() << "=================================";
		QList<int> listCalc;
		for (int i = 0; i < 10; ++i)
		{
			listCalc << i + 1;
		}
		
		static int b = 0; 
		if (!b)
		{
			connect(&w2, SIGNAL(finished()), SLOT(slot_QtConcurunt_mapped_finished()));
			connect(&w2, SIGNAL(progressValueChanged(int)), 
				SLOT(slot_QtConcurunt_mapped_progressValueChanged(int)));
			connect(&w2, SIGNAL(resultReadyAt(int)), 
				SLOT(slot_QtConcurunt_mapped_resultReadyAt(int)));

			connect(&w2, SIGNAL(progressRangeChanged(int, int)),
				SLOT(slot_QtConcurunt_mapped_progressRangeChanged(int ,int )));
			b = 1;
		}


		w2.setFuture(QtConcurrent::mapped(listCalc, calc2));
	}

	void CWidget1::slot_QtConcurunt_mapped_finished()
	{
		qDebug() << "slot_QtConcurunt_mapped_finished:";
// 		for (int i = 0; i < w2.future().resultCount(); ++i)
// 		{
// 			QSharedPointer<stEMDataInfo> re = w2.resultAt(i);
// 
// 			qDebug() << "resultAt(i)";
// 		}
	}

	void CWidget1::slot_QtConcurunt_mapped_progressValueChanged( int progressValue )
	{

	}

	void CWidget1::slot_QtConcurunt_mapped_resultReadyAt( int progressValue )
	{
		stEMDataInfo* re = w2.resultAt(progressValue);
		delete re;
		qDebug() << "slot_QtConcurunt_mapped_resultReadyAt:";
	}

	void CWidget1::slot_QtConcurunt_mapped_progressRangeChanged( int minn, int maxn )
	{
		qDebug() << "slot_QtConcurunt_mapped_progressRangeChanged:" << minn << maxn;
	}

	
	

}