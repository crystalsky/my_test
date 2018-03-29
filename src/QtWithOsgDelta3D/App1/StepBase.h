#ifndef StepBase_h__
#define StepBase_h__

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "glog.h"
#include <QWidget>
#include <QDialog>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTableView>
#include <QPainter>
#include <QMap>
#include <assert.h>

namespace Study_BaseClass
{
	class CWidgetBase : public QWidget
	{
		Q_OBJECT
	public:
		CWidgetBase(QWidget* pParent = NULL) : QWidget(pParent){}
		~CWidgetBase(){}

		virtual void refresh(){}

	protected:
	};

	class CStepBase : public QWidget
	{
		Q_OBJECT
	public:
		CStepBase(QWidget* pParnet);
		~CStepBase();

	public:
		
	protected Q_SLOTS:
		void slotButtonClicek();
	
	protected:
		bool addFunctionalWidget(const QString& strButtonName, CWidgetBase* pFunctionWidget);

	private:
		void init();

	private:
		QStackedWidget*		m_pStackedWidget;
		QVBoxLayout*		m_playButtons;
		QMap<QPushButton*, CWidgetBase*>	m_mapAllFunctionWidget;	
	};
}

namespace Study_BaseClass
{
	class CButtonFunctionWidget : public CWidgetBase
	{
		Q_OBJECT
	Q_SIGNALS:
		void signalButtonClicked(const QString& strFunctionButtonName);
	public:
		CButtonFunctionWidget(QWidget* pParent = NULL);
		~CButtonFunctionWidget(){}

	public:
		void initColumeCount(int nColume = 5){m_nColumeCount = nColume;}

		void addFunctionButton(const QString& strButtonName);
	protected:
		virtual bool onButtonClicek(const QString& strFunctionButtonName)
		{
			emit signalButtonClicked(strFunctionButtonName);
			return true;
		}

	private Q_SLOTS:
		void slotClicked();

	private:
		void addButton(int nRow, int nColume, const QString& strButtonName);
	private:
		QGridLayout*	m_pGridLayout;
		int		m_nCurRow;
		int		m_nCurColume;
		int		m_nColumeCount;

		QMap<QString, QPushButton*>	m_allFunctionalButtons;
	};
}

#endif // StepBase_h__
