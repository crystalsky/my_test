#include "Page1.h"
#include "QtProjectPath.h"
#include "QStyleSheetWidget1.h"
#include "controllerwindow.h"

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
		addFunctionalWidget(QStringLiteral("²âÊÔ´°Ìå_1"), 
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
		addFunctionButton(QStringLiteral("Í¸Ã÷¶Ô»°¿ò²âÊÔ"));
		addFunctionButton(QStringLiteral("MemoryTest"));
		addFunctionButton(QStringLiteral("MemoryTestVector"));
		addFunctionButton(QStringLiteral("QStyleSheet_Test"));
	}

	bool CWidget1::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (strFunctionButtonName == QStringLiteral("Í¸Ã÷¶Ô»°¿ò²âÊÔ"))
		{
			static Gui_Widget1::CQMLTranslucentWidget* pWidget = 
				new Gui_Widget1::CQMLTranslucentWidget();

			pWidget->resize(400, 700);
			pWidget->show();
			pWidget->raise();

			return true;
		}
		else if (strFunctionButtonName == "MemoryTest")
		{
			static double *dval = NULL;
			if (dval == NULL)
			{
				dval = new double[100 * 1024 * 1024];
			}
			else
			{
				delete []dval;
				dval = NULL;
			}
		}
		else if (strFunctionButtonName == "MemoryTestVector")
		{
			/*static std::vector<double> vec;
			if (vec.empty())
			{
				vec.assign(100 * 1024 * 1024, 0);
			}
			else
			{
				//vec.clear();
				vec.swap(std::vector<double>());
			}*/

			static QVector<double> vec;
			if (vec.empty())
			{
				vec.resize(50 * 1024 * 1024);
			}
			else
			{
				vec.clear();
				//vec.swap(std::vector<double>());
			}
		}
		else if (strFunctionButtonName == "QStyleSheet_Test")
		{
			QStyleSheetWidget1* pWidget = new QStyleSheetWidget1();
			pWidget->resize(400, 700);
			pWidget->show();
			pWidget->raise();
		}

		return false;
	}
}