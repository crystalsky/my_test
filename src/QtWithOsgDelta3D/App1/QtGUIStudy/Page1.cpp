#include "Page1.h"
#include "QtProjectPath.h"

namespace Study_QtGui
{
	CPage1::CPage1( QWidget* pParnet )
		: Study_BaseClass::CStepBase(pParnet)
	{
		initFunctionWidgets();
	}

	CPage1::~CPage1()
	{

	}

	void CPage1::initFunctionWidgets()
	{
		addFunctionalWidget(QStringLiteral("���Դ���_1"), 
			new CWidget1(this));
	}

	Gui_Widget1::CQMLTranslucentWidget::CQMLTranslucentWidget()
	{
		setWindowFlags(
			Qt::FramelessWindowHint | 
			Qt::WindowMinimizeButtonHint |
			Qt::WindowSystemMenuHint);

		setAttribute(Qt::WA_TranslucentBackground);
	}

	void Gui_Widget1::CQMLTranslucentWidget::init()
	{

	}

	void Gui_Widget1::CQMLTranslucentWidget::paintEvent( QPaintEvent *ev )
	{
		//QWidget::paintEvent(ev);

		QPainter painter(this);
		painter.setPen(QPen(Qt::red, 2));
		painter.setBrush(Qt::yellow);
		painter.drawRect(0, 0, 100, 100);

	}
}

namespace Study_QtGui
{
	CWidget1::CWidget1( QWidget* pParent /*= NULL*/ ) : CButtonFunctionWidget(pParent)
	{
		init();
	}

	void CWidget1::init()
	{
		addFunctionButton(QStringLiteral("͸���Ի������"));
	}

	bool CWidget1::onButtonClicek( const QString& strFunctionButtonName )
	{
		if (strFunctionButtonName == QStringLiteral("͸���Ի������"))
		{
			static Gui_Widget1::CQMLTranslucentWidget* pWidget = 
				new Gui_Widget1::CQMLTranslucentWidget();

			pWidget->resize(400, 700);
			pWidget->show();
			pWidget->raise();

			return true;
		}
	}
}