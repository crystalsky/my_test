#include "StepBase.h"
#include "QtProjectPath.h"

namespace Study_BaseClass
{
	CStepBase::CStepBase( QWidget* pParnet )
	{
		init();
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

	void CStepBase::slotButtonClicek()
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
		connect(pBtn, SIGNAL(clicked()), SLOT(slotButtonClicek()));
		pBtn->setObjectName(strButtonName);
		m_playButtons->addWidget(pBtn);

		m_mapAllFunctionWidget.insert(pBtn, pFunctionWidget);
		m_pStackedWidget->addWidget(pFunctionWidget);

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
		setLayout(m_pGridLayout);

		initColumeCount();
	}

	void CButtonFunctionWidget::slotClicked()
	{
		QPushButton* pbutton = qobject_cast<QPushButton*>(sender());

		if (pbutton)
		{
			onButtonClicek(pbutton->objectName());
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