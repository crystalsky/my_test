#include "Step1.h"
#include "QtProjectPath.h"
#include "piechart.h"
#include <QTimerEvent>
#include <QDateTime>
#include "ColorMaker.h"
#include "ImageProcessor.h"

namespace Study_QML
{
	CStep1::CStep1( QWidget* pParnet )
		: QtUI::CStepBase(pParnet)
	{
		initFunctionWidgets();
	}

	CStep1::~CStep1()
	{

	}

	void CStep1::initFunctionWidgets()
	{
		addFunctionalWidget(QStringLiteral("Run_QMLScene_Exe"), 
			new CQMLSceneWidget_BaseTest(this));

		addFunctionalWidget(QStringLiteral("Run_QMLScene_Animation"), 
			new CQMLSceneWidget_Animation(this));

		addFunctionalWidget(QStringLiteral("CXX_PieChart"), 
			new chapter1_basics_piechart(this));

		addFunctionalWidget(QStringLiteral("CXX_ColorMaker"),
			new ColorMakerWidget(this));

		addFunctionalWidget(QStringLiteral("CXX_ImageProcessor"),
			new ImageProcessorWidget(this));
	}
}

namespace Study_QML
{
	chapter1_basics_piechart::chapter1_basics_piechart(QWidget* pParent)
		: QtUI::CWidgetBase(pParent)
		, m_pQuitWidget(NULL)
	{
		m_pLay = new QVBoxLayout;
		setLayout(m_pLay);

		refresh();
	}

	chapter1_basics_piechart::~chapter1_basics_piechart()
	{

	}

	void chapter1_basics_piechart::refresh()
	{
		if (m_pQuitWidget)
		{
			m_pQuitWidget->close();
		}

		qmlRegisterType<PieChart>("Charts", 1, 0, "PieChart");

		QQuickView *m_pView = new QQuickView();
		const QString& strFile = QtProjectPath::FilePath::GetQMLFilePath("piechart.qml");
		m_pView->setSource(QUrl::fromLocalFile(strFile));

		m_pQuitWidget = QWidget::createWindowContainer(m_pView, this);
		m_pQuitWidget->setAttribute(Qt::WA_DeleteOnClose);

		m_pLay->addWidget(m_pQuitWidget);
	}
}

namespace Study_QML
{
	CQMLSceneWidget_BaseTest::CQMLSceneWidget_BaseTest( QWidget* pParent /*= NULL*/ ) 
		: CQMLSceneWidget(pParent)
	{
		init();
	}

	void CQMLSceneWidget_BaseTest::init()
	{
		_addFunction("base_Info");
		_addFunction("Tutorial_1_Basic_Types");
		_addFunction("property_binding");

		_addFunction(QStringLiteral("附加信号处理器_1"), false);
		_addFunction(QStringLiteral("Connection_1"));

		_addFunction("img_test2");
		_addFunction("usersignal");
		_addFunction("signal_connect");
		_addFunction("ColorPickerTest");
		_addFunction("dynamic_componet");
		_addFunction("qt_create_componet");
		_addFunction("row");
		_addFunction("column");
		_addFunction("grid");
		//////////////////////////////////////////////////////////////////////////
		_addFunction("samegame", false);
		//////////////////////////////////////////////////////////////////////////
		_addFunction("DisplaySelectGroupBox");
		_addFunction("DisplaySelectGroupBox_Process");
		//////////////////////////////////////////////////////////////////////////
		
	}

	bool CQMLSceneWidget_BaseTest::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (CQMLSceneWidget::onButtonClicked(strFunctionButtonName))
		{
			return true;
		}

		if (strFunctionButtonName == QStringLiteral("附加信号处理器_1"))
		{
			Study_QML::runQMLSceneProcess("AttachedPropertiesSignalHandler.qml", this);
		}
		else if (strFunctionButtonName == QStringLiteral("samegame"))
		{
			Study_QML::runQMLSceneProcess("samegame/main.qml", this);
		}

		return true;
	}
}

namespace Study_QML
{
	CQMLSceneWidget_Animation::CQMLSceneWidget_Animation( QWidget* pParent /*= NULL*/ ) 
		: CQMLSceneWidget(pParent)
	{
		init();
	}

	void CQMLSceneWidget_Animation::init()
	{
		_addFunction("propertyanimation_standalone");
	}

	bool CQMLSceneWidget_Animation::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (CQMLSceneWidget::onButtonClicked(strFunctionButtonName))
		{
			return true;
		}

		if (strFunctionButtonName == QStringLiteral("附加信号处理器_1"))
		{
			Study_QML::runQMLSceneProcess("AttachedPropertiesSignalHandler.qml", this);
		}
		else if (strFunctionButtonName == QStringLiteral("samegame"))
		{
			Study_QML::runQMLSceneProcess("samegame/main.qml", this);
		}

		return true;
	}
}