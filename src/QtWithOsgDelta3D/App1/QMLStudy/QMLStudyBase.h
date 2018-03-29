#ifndef QMLStudyBase_h__
#define QMLStudyBase_h__

#include <QWidget>
#include <QQuickView>
#include <QUrl>
#include "../StepBase.h"
#include <QProcess>
#include "QtProjectPath.h"

namespace Study_QML
{
	class CQMLWidgetBase : public Study_BaseClass::CWidgetBase
	{
		Q_OBJECT
	public:
		CQMLWidgetBase(const QString& strQMLFile, QWidget* pParent = NULL);
		~CQMLWidgetBase();

		virtual void refresh();

	private:
		QWidget*		m_pQuitWidget;
		QVBoxLayout*	m_pLay;
		QUrl			m_url;
	};
}

namespace Study_QML
{
	class CQMLSceneProcess : public QObject
	{
		Q_OBJECT
	public:
		CQMLSceneProcess(const QString& strQMLFile, QObject* pParent = NULL);
		~CQMLSceneProcess();

		bool runProcess();

		protected Q_SLOTS:
			void slotReadyReadStandardError();
	private:
		QProcess*	m_processQMLScene;
		QString		m_strQMLFileName;
	};

	static bool runQMLSceneProcess(const QString& strQMLFile, QObject* pParent)
	{
		if (strQMLFile.isEmpty())
		{
			return false;
		}
		Study_QML::CQMLSceneProcess* p = 
			new Study_QML::CQMLSceneProcess(strQMLFile, pParent);

		return p->runProcess();
	}
}

namespace Study_QML
{
	class CQuickViewWidgetBase : public Study_BaseClass::CWidgetBase
	{
		Q_OBJECT
	public:
		CQuickViewWidgetBase(const QString& strQMLFileName, QWidget* pParent = NULL);
		~CQuickViewWidgetBase();

		virtual void refresh();
	protected:
		bool createQMLWidget(const QString& strQmlFilePathName);

		void setQMLFileName(const QString& strQMLFileName){m_strQMLFileName = strQMLFileName;}
	private:
		QWidget*	m_pQuitWidget;
		QVBoxLayout* m_pLay;
		QString		m_strQMLFileName;
	};
}

namespace Study_QML
{
	class CQMLSceneWidget : public Study_BaseClass::CButtonFunctionWidget
	{
	public:
		CQMLSceneWidget(QWidget* pParent = NULL);
		~CQMLSceneWidget(){}
	protected:
		void _addFunction(const QString& strFunctionName, bool bAutoFunction = true);

	protected:
		virtual bool onButtonClicek(const QString& strFunctionButtonName);

	private:
		QStringList m_listAutoRunFunctions;
	};
}

#endif // QMLStudyBase_h__
