#include "StepBase.h"
#include "QtProjectPath.h"

namespace Study_BaseClass
{
	CTabWidget::CTabWidget( QWidget* pParent /*= NULL*/ )
	{
		init();
	}

	CTabWidget::~CTabWidget()
	{

	}

	void CTabWidget::init()
	{
		m_pTabWidget = new QTabWidget(this);
		
		QVBoxLayout* pLay = new QVBoxLayout;
		pLay->addWidget(m_pTabWidget);
		pLay->setContentsMargins(3, 3, 3, 3);

		setLayout(pLay);
	}

	bool CTabWidget::addTabWidget( const QString& strName, QWidget* pWidget )
	{
		QString strTablename = strName;
		if (pWidget == NULL)
		{
			return false;
		}

		if (strTablename.isEmpty())
		{
			static int nIndex = 1;
			strTablename = QString("DefaultWidget_1%").arg(nIndex++);
		}

		m_pTabWidget->addTab(pWidget, strTablename);

		return true;
	}
}

namespace Study_BaseClass
{
	CButtonFunctionWidget::CButtonFunctionWidget( QWidget* pParent /*= NULL*/ )
		: CWidgetBase(pParent)
		, m_nCurColume(0)
		, m_nCurRow(0)
	{
		m_pGridLayout = new QGridLayout;
		m_pGridLayout->setContentsMargins(3, 3, 3, 3);
		setLayout(m_pGridLayout);

		initColumeCount();
	}

	CButtonFunctionWidget::CButtonFunctionWidget(int nColNum, QWidget* pParent)
	{
		m_pGridLayout = new QGridLayout;
		m_pGridLayout->setContentsMargins(3, 3, 3, 3);
		setLayout(m_pGridLayout);

		initColumeCount(nColNum);
	}

	void CButtonFunctionWidget::initColumeCount( int nColume /*= 5*/ )
	{
		m_nColumeCount = nColume;
		if (nColume < 1)
		{
			m_nColumeCount = 1;
		}
	}

	void CButtonFunctionWidget::slotClicked()
	{
		QPushButton* pbutton = qobject_cast<QPushButton*>(sender());

		if (pbutton)
		{
			onButtonClicked(pbutton->objectName());
		}
	}

	void CButtonFunctionWidget::addFunctionButton( const QString& strButtonName )
	{
		if (m_allFunctionalButtons.contains(strButtonName))
		{
			LOG(ERROR) << "=====There is Exist The " << strButtonName.toLocal8Bit().data();
			return;
		}

		if (m_nCurColume >= m_nColumeCount)
		{
			m_nCurColume = 0;
			m_nCurRow++;
		}

		m_nCurColume++;
		addButton(m_nCurRow, m_nCurColume, strButtonName);
	}

	void CButtonFunctionWidget::addButton( int nRow, int nColume, const QString& strButtonName )
	{
		QPushButton* pButton = new QPushButton(strButtonName, this);
		pButton->setObjectName(strButtonName);
		connect(pButton, SIGNAL(clicked()), SLOT(slotClicked()));

		m_pGridLayout->addWidget(pButton, nRow, nColume);

		m_allFunctionalButtons[strButtonName] = pButton;
	}
}

namespace Study_BaseClass
{
	CStepBase::CStepBase( QWidget* pParnet )
		: QWidget(pParnet)
		, m_ButtonColNum(1)
	{
		init();
	}

	CStepBase::CStepBase(int nButtonColNum, QWidget* pParnet)
		: QWidget(pParnet)
		, m_ButtonColNum(nButtonColNum)
	{
		if (m_ButtonColNum < 1)
		{
			m_ButtonColNum = 1;
		}
	}

	CStepBase::~CStepBase()
	{

	}

	void CStepBase::init()
	{
		m_playButtons = new QVBoxLayout;
		m_pStackedWidget = new QStackedWidget;

		QVBoxLayout* playOutLeft = new QVBoxLayout;
		playOutLeft->addLayout(m_playButtons);
		playOutLeft->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));

		QHBoxLayout* pHLay = new QHBoxLayout;
		pHLay->setStretch(0, 1);
		pHLay->setStretch(1, 99);
		pHLay->addLayout(playOutLeft);
		pHLay->addWidget(m_pStackedWidget);
		setLayout(pHLay);
	}

	void CStepBase::slotButtonClicked()
	{
		QPushButton* pBtn = qobject_cast<QPushButton*>(sender());
		CWidgetBase* pWidget = m_mapAllFunctionWidget.value(pBtn, NULL);
		if (NULL != pWidget)
		{
			m_pStackedWidget->setCurrentWidget(pWidget);
			pWidget->refresh();
		}
	}

	bool CStepBase::addFunctionalWidget(const QString& strButtonName, CWidgetBase* pFunctionWidget )
	{
		if (NULL == pFunctionWidget || 
			m_mapAllFunctionWidget.values().contains(pFunctionWidget))
		{
			return false;
		}

		QPushButton* pBtn = new QPushButton(strButtonName, this);
		connect(pBtn, SIGNAL(clicked()), SLOT(slotButtonClicked()));
		pBtn->setObjectName(strButtonName);
		m_playButtons->addWidget(pBtn);

		m_mapAllFunctionWidget.insert(pBtn, pFunctionWidget);
		m_pStackedWidget->addWidget(pFunctionWidget);

		return true;
	}
}

namespace Study_BaseClass
{
	CStepBaseEx::CStepBaseEx( QWidget* pParnet )
		: QWidget(pParnet)
	{
		m_pButtonFunctionWidget = new CButtonFunctionWidget(1, this);
		connect(m_pButtonFunctionWidget,
			SIGNAL(signalButtonClicked(const QString&)),
			SLOT(slotButtonClicked(const QString&)));
		init();
	}

	CStepBaseEx::CStepBaseEx(int nButtonColNum, QWidget* pParnet)
		: QWidget(pParnet)
	{
		m_pButtonFunctionWidget = new CButtonFunctionWidget(nButtonColNum, this);
		connect(m_pButtonFunctionWidget,
			SIGNAL(signalButtonClicked(const QString&)),
			SLOT(slotButtonClicked(const QString&)));
		init();
	}

	CStepBaseEx::~CStepBaseEx()
	{

	}

	void CStepBaseEx::init()
	{
		m_pStackedWidget = new QStackedWidget;

		QHBoxLayout* pHLay = new QHBoxLayout;
		pHLay->setContentsMargins(3, 3, 3, 3);
		pHLay->setStretch(0, 20);
		pHLay->setStretch(1, 80);
		pHLay->addWidget(m_pButtonFunctionWidget);
		pHLay->addWidget(m_pStackedWidget);
		setLayout(pHLay);
	}

	void CStepBaseEx::slotButtonClicked(const QString& strFunctionButtonName)
	{
		CWidgetBase* pWidget = m_mapAllFunctionWidget.value(strFunctionButtonName, NULL);
		if (NULL != pWidget)
		{
			m_pStackedWidget->setCurrentWidget(pWidget);
			pWidget->refresh();
		}
	}

	bool CStepBaseEx::addFunctionalWidget(const QString& strButtonName, CWidgetBase* pFunctionWidget )
	{
		if (NULL == pFunctionWidget || 
			m_mapAllFunctionWidget.values().contains(pFunctionWidget))
		{
			return false;
		}

		QPushButton* pBtn = new QPushButton(strButtonName, this);
		connect(pBtn, SIGNAL(clicked()), SLOT(slotButtonClicked()));
		pBtn->setObjectName(strButtonName);

		m_mapAllFunctionWidget.insert(pBtn->objectName(), pFunctionWidget);
		m_pStackedWidget->addWidget(pFunctionWidget);

		return true;
	}
}
