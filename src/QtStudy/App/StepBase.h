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
	/*! 此类提供QTabWidget以扩展横向界面 */
	class CTabWidget : public QWidget
	{
	public:
		CTabWidget(QWidget* pParent = NULL);
		~CTabWidget();

		bool addTabWidget(const QString& strName, QWidget* pWidget);
	private:
		void init();

	protected:
		QTabWidget*		m_pTabWidget;
	};
}

namespace Study_BaseClass
{
	/*! 此类提供一个基接口处理 */
	class CWidgetBase : public QWidget
	{
		Q_OBJECT
	public:
		CWidgetBase(QWidget* pParent = NULL) : QWidget(pParent){}
		~CWidgetBase(){}

		virtual void refresh(){}

	protected:
	};
}

namespace Study_BaseClass
{
	/*! 此类提供一个GridLayout的基Widget,可以增加多个行列的功能按钮 */
	/*! 重写onButtonClicked */
	class CButtonFunctionWidget : public CWidgetBase
	{
		Q_OBJECT
	Q_SIGNALS:
		void signalButtonClicked(const QString& strFunctionButtonName);
	public:
		CButtonFunctionWidget(QWidget* pParent = NULL);
		CButtonFunctionWidget(int nColNum, QWidget* pParent = NULL);
		~CButtonFunctionWidget(){}

	public:
		void initColumeCount(int nColume = 5);

		void addFunctionButton(const QString& strButtonName);
	protected:
		virtual bool onButtonClicked(const QString& strFunctionButtonName)
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

namespace Study_BaseClass
{
	//此类提供左面板为功能键, 右面板为QStackWidget为原型的基础窗体
	class CStepBase : public QWidget
	{
		Q_OBJECT
	public:
		CStepBase(QWidget* pParnet);
		CStepBase(int nButtonColNum, QWidget* pParnet);
		~CStepBase();

	public:
		
	protected Q_SLOTS:
		void slotButtonClicked();
	
	protected:
		bool addFunctionalWidget(const QString& strButtonName, CWidgetBase* pFunctionWidget);

	private:
		void init();

	private:
		QStackedWidget*		m_pStackedWidget;
		QVBoxLayout*		m_playButtons;

		int					m_ButtonColNum;	
		QMap<QPushButton*, CWidgetBase*>	m_mapAllFunctionWidget;	
	};

	//此类提供左面板为功能键, 右面板为QStackWidget为原型的基础窗体
	class CStepBaseEx : public QWidget
	{
		Q_OBJECT
	public:
		CStepBaseEx(QWidget* pParnet);
		CStepBaseEx(int nButtonColNum, QWidget* pParnet);
		~CStepBaseEx();

	public:
	
	protected Q_SLOTS:
		virtual void slotButtonClicked(const QString& strFunctionButtonName);

	protected:
		bool addFunctionalWidget(const QString& strButtonName, CWidgetBase* pFunctionWidget);

	private:
		void init();

	private:
		QStackedWidget*		m_pStackedWidget;
		QMap<QString, CWidgetBase*>	m_mapAllFunctionWidget;	

		CButtonFunctionWidget* m_pButtonFunctionWidget;
	};
}


#endif // StepBase_h__
