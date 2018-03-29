#include "QMLStudyBase.h"
#include <QDir>
#include <boost/format.hpp>


namespace Study_QML
{
	CQMLWidgetBase::CQMLWidgetBase(const QString& strQMLFile, QWidget* pParent)
		: Study_BaseClass::CWidgetBase(pParent)
		, m_pQuitWidget(NULL)
	{
		m_pLay = new QVBoxLayout;
		setLayout(m_pLay);

		const QString& strFilePath = QtProjectPath::FilePath::GetQMLFilePath(strQMLFile);
		m_url = QUrl::fromLocalFile(strFilePath);

		assert(m_url.isValid());
		if (m_url.isValid())
		{
			refresh();
		}
	}

	CQMLWidgetBase::~CQMLWidgetBase()
	{

	}

	void CQMLWidgetBase::refresh()
	{
		if (m_pQuitWidget)
		{
			m_pQuitWidget->close();
		}

		QQuickView *m_pView = new QQuickView();
		m_pView->setSource(m_url);

		m_pQuitWidget = QWidget::createWindowContainer(m_pView, this);
		m_pQuitWidget->setAttribute(Qt::WA_DeleteOnClose);

		m_pLay->addWidget(m_pQuitWidget);
	}
}

namespace Study_QML
{
	CQMLSceneWidget::CQMLSceneWidget( QWidget* pParent /*= NULL*/ ) 
		: Study_BaseClass::CButtonFunctionWidget(pParent)
	{

	}

	void CQMLSceneWidget::_addFunction( const QString& strFunctionName, bool bAutoFunction /*= true*/ )
	{
		if (bAutoFunction)
		{
			m_listAutoRunFunctions << strFunctionName;
		}

		addFunctionButton(strFunctionName);
	}

	bool CQMLSceneWidget::onButtonClicek( const QString& strFunctionButtonName )
	{
		const QString& strQmlFileName = QString("%1.qml").arg(strFunctionButtonName);
		if (m_listAutoRunFunctions.contains(strFunctionButtonName) &&
			Study_QML::runQMLSceneProcess(strQmlFileName, this))
		{
			return true;
		}

		return false;
	}

}

namespace Study_QML
{
	CQMLSceneProcess::CQMLSceneProcess(const QString& strQMLFile, QObject* pParent)
		: QObject(pParent)
	{
		m_processQMLScene = new QProcess(this);
		m_strQMLFileName = strQMLFile;

		m_processQMLScene->setReadChannel(QProcess::StandardError);
		connect(m_processQMLScene, SIGNAL(readyReadStandardError()), 
			SLOT(slotReadyReadStandardError()));
	}

	CQMLSceneProcess::~CQMLSceneProcess()
	{

	}

	bool CQMLSceneProcess::runProcess()
	{
		const QString& strFilePath = QtProjectPath::FilePath::GetQMLFilePath(m_strQMLFileName);
		if (!QDir().exists(strFilePath))
		{
			LOG(ERROR) << "Not Exist QML File: " << strFilePath.toLocal8Bit().data();
			return false;
		}

		QStringList listParam;
		listParam << strFilePath;

		m_processQMLScene->start("qmlscene.exe", listParam);

		return true;
	}

	void CQMLSceneProcess::slotReadyReadStandardError()
	{
		const QString str = m_processQMLScene->readLine();
		if (str.contains("file:"))
		{
			LOG(ERROR) << "..." << str.toLocal8Bit().data();
		}
	}
}

namespace Study_QML
{
	CQuickViewWidgetBase::CQuickViewWidgetBase(const QString& strQMLFileName, QWidget* pParent)
		: Study_BaseClass::CWidgetBase(pParent)
		, m_pQuitWidget(NULL)
	{
		m_pLay = new QVBoxLayout;
		setLayout(m_pLay);

		setQMLFileName(strQMLFileName);
	}

	CQuickViewWidgetBase::~CQuickViewWidgetBase()
	{

	}

	bool CQuickViewWidgetBase::createQMLWidget(const QString& strQmlFilePathName)
	{
		if (m_pQuitWidget)
		{
			m_pQuitWidget->close();
		}

		QQuickView *m_pView = new QQuickView();
		m_pView->setSource(QUrl::fromLocalFile(strQmlFilePathName));

		m_pQuitWidget = QWidget::createWindowContainer(m_pView, this);
		m_pQuitWidget->setAttribute(Qt::WA_DeleteOnClose);

		return true;
	}

	void CQuickViewWidgetBase::refresh()
	{
		if (m_strQMLFileName.isEmpty())
		{
			LOG(WARNING) << "QMLFile Name Not Exist...!";
			return;
		}
		const QString& strFile = QtProjectPath::FilePath::GetQMLFilePath(m_strQMLFileName);

		QFileInfo fi(strFile);
		if (!fi.exists())
		{
			LOG(WARNING) << boost::format("QMLFile Path %s Not Exist...!") % strFile.toLocal8Bit().data();
			return;
		}

		createQMLWidget(strFile);

		m_pLay->addWidget(m_pQuitWidget);
	}
}