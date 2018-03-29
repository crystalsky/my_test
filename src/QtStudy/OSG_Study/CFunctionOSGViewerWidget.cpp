#include "CFunctionOSGViewerWidget.h"
#include <QGroupBox>
#include "OSGBaseDef.h"
#include <glog.h>

CFunctionOSGViewerWidget::CFunctionOSGViewerWidget( QWidget* pParnet )
	: QWidget(pParnet)
	, m_pLabelTitle(NULL)
	, m_pGroupBox(NULL)
{
	_init();
}

CFunctionOSGViewerWidget::CFunctionOSGViewerWidget(const QString& strTitle, QWidget* pParnet )
	: QWidget(pParnet)
	, m_pLabelTitle(NULL)
	, m_pGroupBox(NULL)
{
	_init();
	setTitle(strTitle);
}

CFunctionOSGViewerWidget::CFunctionOSGViewerWidget(int nButtonColNum, QWidget* pParnet)
	: QWidget(pParnet)
	, m_pLabelTitle(NULL)
	, m_pGroupBox(NULL)
{
	_init(nButtonColNum);
}

CFunctionOSGViewerWidget::CFunctionOSGViewerWidget(const QString& strTitle, int nButtonColNum, QWidget* pParnet)
	: QWidget(pParnet)
	, m_pLabelTitle(NULL)
	, m_pGroupBox(NULL)
{
	_init(nButtonColNum);
	setTitle(strTitle);
}


CFunctionOSGViewerWidget::~CFunctionOSGViewerWidget()
{
	QMapIterator<QString, OSGFuncBase*> it(m_mapNamedOSGFunc);
	while (it.hasNext())
	{
		delete it.next().value();
	}
	m_mapNamedOSGFunc.clear();
}

void CFunctionOSGViewerWidget::_init(int nButtonColNum)
{
	m_pButtonFunctionWidget = new QtUI::CButtonFunctionWidget(this);
	connect(m_pButtonFunctionWidget,
		SIGNAL(signalButtonClicked(const QString&)),
		SLOT(slotButtonClicked(const QString&)));
	{
		m_pButtonFunctionWidget->setStyleSheet(
			"background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\
				stop:0 yellow, stop:1 green)"
		);
	}

	{
		QVBoxLayout* pLayOut = new QVBoxLayout(this);
		m_pGroupBox = new QGroupBox(this);
		pLayOut->setContentsMargins(3, 9, 3, 3);
		pLayOut->addWidget(m_pGroupBox);

		m_pGroupBox->setStyleSheet(
			"QGroupBox {\
			background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
			stop: 0 #E0E0E0, stop: 1 #FFFFFF);\
			border: 2px solid blue;\
			border-radius: 5px;\
			font-size: 16px;\
			font-weight: bold;\
			}\
			QGroupBox::title {\
			subcontrol-origin: margin;\
			subcontrol-position: top center; /* position at the top center */\
			color: blue;\
			background-color: yellow;\
			}\
			");
	}

	{
		QVBoxLayout* pLayOutUpDown = new QVBoxLayout(m_pGroupBox);
		pLayOutUpDown->setContentsMargins(3, 15, 3, 3);
		pLayOutUpDown->setSpacing(3);
		{
			m_pLabelTitle = new QLabel(this);
			pLayOutUpDown->addWidget(m_pLabelTitle);
			m_pLabelTitle->setVisible(false);
			m_pLabelTitle->setFixedHeight(40);
		}
		{
			m_pLayoutMain = new QHBoxLayout();

			m_pLayoutMain->setContentsMargins(1, 1, 1, 1);
			m_pLayoutMain->addWidget(m_pButtonFunctionWidget);

			QGroupBox* pWidget = new QGroupBox(this);
			m_pLayoutMain->addWidget(pWidget);

			m_pStackedWidget = new QStackedWidget(this);
			QVBoxLayout* pLay = new QVBoxLayout(pWidget);
			pLay->setContentsMargins(0, 0, 0, 0);
			pLay->addWidget(m_pStackedWidget);

			pLayOutUpDown->addLayout(m_pLayoutMain);
		}

		m_pViewerWidget = new ViewerWidget;
		m_pStackedWidget->addWidget(m_pViewerWidget);
		setToDefaultViewerWidget();
	}

	if (nButtonColNum == 1)
	{
		setLayoutMainStrech(10, 70);
	}
	else if (nButtonColNum == 2)
	{
		setLayoutMainStrech(15, 70);
	}
}

void CFunctionOSGViewerWidget::setLayoutMainStrech( int strech1, int strech2 )
{
	if (m_pLayoutMain)
	{
		m_pLayoutMain->setStretch(0, strech1);
		m_pLayoutMain->setStretch(1, strech2);
	}
}

void CFunctionOSGViewerWidget::setToDefaultViewerWidget()
{
	if (m_pStackedWidget)
	{
		m_pStackedWidget->setCurrentWidget(m_pViewerWidget);
	}
}

void CFunctionOSGViewerWidget::setLabelContent( const QString& strLabelTitle )
{
	if (m_pLabelTitle)
	{
		m_pLabelTitle->setText(strLabelTitle);
		m_pLabelTitle->setVisible(!strLabelTitle.isEmpty());
	}
}

void CFunctionOSGViewerWidget::setTitle( const QString& strTitle )
{
	if (m_pGroupBox)
	{
		m_pGroupBox->setTitle(strTitle);
	}
}

void CFunctionOSGViewerWidget::slotButtonClicked( const QString& strFunctionButtonName )
{
	OSGFuncBase* pFuncBase = _getOSGFuncBase(strFunctionButtonName);
	
	if (pFuncBase)
	{
		osg::Node* pNode = pFuncBase->getNode();

		//默认用默认的窗体显示
		ViewerWidget* pWidget = m_pViewerWidget;
		if (pFuncBase->hasOwnerViewerWidget() && 
			pFuncBase->getViewerWidget() != NULL)
		{
			//用对象创建的Viewer显示
			pWidget = pFuncBase->getViewerWidget();
		}
		
		m_pStackedWidget->setCurrentWidget(pWidget);
		pWidget->setSceneData(pNode);
	}
}

OSGFuncBase* CFunctionOSGViewerWidget::_getOSGFuncBase( const QString& strFunctionButtonName )
{
	OSGFuncBase* pFuncBase = NULL;
	if (!m_mapNamedOSGFunc.contains(strFunctionButtonName))
	{
		pFuncBase = 
			UtilityKit::CReflectedObject::createEx<OSGFuncBase>(
			strFunctionButtonName.toLocal8Bit().data());
		if (pFuncBase == NULL)
		{
			LOG(ERROR) << "No Reflect Class Name: " << 
				strFunctionButtonName.toLocal8Bit().data();
			return NULL;
		}

		m_mapNamedOSGFunc[strFunctionButtonName] = pFuncBase;

		pFuncBase->init();

		if (pFuncBase->hasOwnerViewerWidget() && 
			pFuncBase->getViewerWidget() != NULL)
		{
			ViewerWidget* pWidget = pFuncBase->getViewerWidget();
			m_pStackedWidget->addWidget(pWidget);
		}
	}
	else
	{
		pFuncBase = m_mapNamedOSGFunc.value(strFunctionButtonName);
	}

	return pFuncBase;
}

bool CFunctionOSGViewerWidget::addFunctional(const QString& strButtonName )
{
	m_pButtonFunctionWidget->addFunctionButton(strButtonName);

	return true;
}
