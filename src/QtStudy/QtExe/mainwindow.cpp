
#include <QtWidgets>
#include "mainwindow.h"
#include "QMLStudy/widget_QMLStudy.h"
#include "QtGUIStudy/widget_QtGuiStudy.h"
#include "QtCoreStudy/widget_QtCoreStudy.h"
#include "demo_dialog.h"
#include <TTimePrint.h>
#include "QtCoreStudy/Page_QtWithCPP.h"
#include "DesignPatternStudy/DesignPatternWidget.h"
#include "BoostStudy/widget_BoostStudy.h"
#include "_xerces-c/xerces_test_widget.h"
#include "template/template_test_widget.h"
#include "XmlSerialize/XmlSerialize_Test_Widget.h"
//! [0]

//! [1]
MainWindow::MainWindow()
{
	QString str = QStringLiteral("我是");

	m_pCenterStackWidget = new CenterActionStackWidget(this);
	setCentralWidget(m_pCenterStackWidget);

    createActions();

    createMenus();

    createToolBars();

    createStatusBar();

    createDockWindows();

    setWindowTitle(tr("Dock Widgets"));
	
	initFunctionalWidgets();

	_readSetting();

	setAcceptDrops(true);

	_startLastAction();
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Dock Widgets"),
            tr("The <b>Dock Widgets</b> example demonstrates how to "
               "use Qt's dock widgets. You can enter your own text, "
               "click a customer to add a customer name and "
               "address, and click standard paragraphs to add them."));
}


void MainWindow::createActions()
{
    
}

void MainWindow::createMenus()
{
	m_pMenu_QtGUI = menuBar()->addMenu(QStringLiteral("QtGui"));
	m_pMenu_QML = menuBar()->addMenu(QStringLiteral("QML"));
	m_pMenu_QtCore = menuBar()->addMenu(QStringLiteral("QtCore"));
	m_pMenu_Boost = menuBar()->addMenu(QStringLiteral("Boost"));
	m_pMenu_PatternDesign = menuBar()->addMenu(QStringLiteral("PatternDesign"));
	m_pMenu_Template = menuBar()->addMenu(QStringLiteral("Template"));
	m_pMenu_OtherTest = menuBar()->addMenu(QStringLiteral("OtherTest"));
}

void MainWindow::createToolBars()
{
//     fileToolBar = addToolBar(tr("File"));
//     fileToolBar->addAction(newLetterAct);
//     fileToolBar->addAction(saveAct);
//     fileToolBar->addAction(printAct);
// 
//     editToolBar = addToolBar(tr("Edit"));
//     editToolBar->addAction(undoAct);
}

//! [8]
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
//! [8]

//! [9]
void MainWindow::createDockWindows()
{

    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customerList = new QListWidget(dock);
    customerList->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(customerList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
   

    dock = new QDockWidget(tr("Paragraphs"), this);
    paragraphsList = new QListWidget(dock);
    paragraphsList->addItems(QStringList()
            << "Thank you for your payment which we have received today."
            << "Your order has been dispatched and should be with you "
               "within 28 days."
            << "We have dispatched those items that were in stock. The "
               "rest of your order will be dispatched once all the "
               "remaining items have arrived at our warehouse. No "
               "additional shipping charges will be made."
            << "You made a small overpayment (less than $5) which we "
               "will keep on account for you, or return at your request."
            << "You made a small underpayment (less than $1), but we have "
               "sent your order anyway. We'll add this underpayment to "
               "your next bill."
            << "Unfortunately you did not send enough money. Please remit "
               "an additional $. Your order will be dispatched as soon as "
               "the complete amount has been received."
            << "You made an overpayment (more than $5). Do you wish to "
               "buy more items, or should we return the excess to you?");
    dock->setWidget(paragraphsList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

void MainWindow::slotAction()
{
	QAction* pAction = qobject_cast<QAction*>(sender());
	if (pAction != NULL)
	{
		m_strLastAction = pAction->objectName();
	}
}

void MainWindow::_readSetting()
{
	QSettings settings("xStudyx", QCoreApplication::instance()->applicationName());
	bool b = restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());

	m_strLastAction = settings.value("LastActionName", "NONE").toString();
}

void MainWindow::_saveSetting()
{
	QSettings settings("xStudyx", QCoreApplication::instance()->applicationName());
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());

	QSettings setting(qApp->applicationDirPath() + "/setting.ini", QSettings::IniFormat);
	setting.setIniCodec(QTextCodec::codecForLocale());
	setting.beginGroup(QStringLiteral("第一组"));
	setting.setValue("AAA", "BBB");

	settings.setValue("LastActionName", m_strLastAction);
}

void MainWindow::closeEvent( QCloseEvent *e )
{
	QMainWindow::closeEvent(e);

	_saveSetting();
}

void MainWindow::initFunctionalWidgets()
{
	TTRestart;
	{//QtGUI
		{
			QAction* pAction = 
				_addFunctionAction(new CWidget_QMLGui(this), 
				QStringLiteral("Page1"), QIcon(":/images/new.png"));
			m_pMenu_QtGUI->addAction(pAction);
		}
		TTPrintAndRestart("QMLGui Time");
	}
	{//QML
		{
			QAction* pAction = 
				_addFunctionAction(new CWidget_QMLStudy(this), 
				QStringLiteral("Tutorials"), QIcon(":/images/new.png"));
			m_pMenu_QML->addAction(pAction);
		}
		TTPrintAndRestart("QMLStudy Time");
	}
	{//QtCore
		{
			QAction* pAction = 
				_addFunctionAction(new Study_QtCore::CStudyWidget(this), 
				QStringLiteral("QtConcurunt"), QIcon(":/images/new.png"));
			m_pMenu_QtCore->addAction(pAction);
		}
		{
			QAction* pAction = 
				_addFunctionAction(new Study_QtCore::CPage_QtWithCPP(this), 
				QStringLiteral("QtWithCPP"), QIcon(":/images/new.png"));
			m_pMenu_QtCore->addAction(pAction);
		}
		TTPrintAndRestart("QtCore Time");
	}
	{//Boost
		{
			QAction* pAction = 
				_addFunctionAction(new Study_Boost::CWidget_BoostStudy(this), 
				QStringLiteral("widget_boost"), QIcon(":/images/new.png"));
			pAction->setShortcuts(QKeySequence::New);
			m_pMenu_Boost->addAction(pAction);
		}
		TTPrintAndRestart("Boost Time");
	}
	
	{//PatternDesign
		QAction* pAction = 
			_addFunctionAction(new DesignPattern::DesignPatternWidget(this), 
			QStringLiteral("TheZenOfDesignPattern"), QIcon(":/images/new.png"));
		//pAction->setShortcuts(QKeySequence::New);
		m_pMenu_PatternDesign->addAction(pAction);
	}
	{//
		QAction* pAction = 
			_addFunctionAction(new template_test_widget(this), 
			QStringLiteral("template_test_widget"), QIcon(":/images/new.png"));
		//pAction->setShortcuts(QKeySequence::New);
		m_pMenu_Template->addAction(pAction);
	}
	{//OtherTest
		{
			QAction* pAction = 
				_addFunctionAction(new Demo_Dialog(this), 
				QStringLiteral("QtPickColor"), QIcon(":/images/new.png"));
			m_pMenu_OtherTest->addAction(pAction);
			TTPrint("QtPickColor");
		}

		{
			QAction* pAction = 
				_addFunctionAction(new xerces_test_widget(this), 
				QStringLiteral("xerces-c"), QIcon(":/images/new.png"));
			m_pMenu_OtherTest->addAction(pAction);
			TTPrint("xerces-c");
		}

		{
			QAction* pAction = 
				_addFunctionAction(new XmlSerialize_Test_Widget(this), 
				QStringLiteral("XmlSerialize"), QIcon(":/images/new.png"));
			m_pMenu_OtherTest->addAction(pAction);
			TTPrint("QtPickColor");
		}
	}
}

QAction* MainWindow::_addFunctionAction(QWidget* pWidget, const QString& strActionName, const QIcon& icon)
{
	QAction* pAction = new QAction(icon, strActionName, this);
	pAction->setObjectName(strActionName);
	connect(pAction, SIGNAL(triggered()), SLOT(slotAction()));

	m_pCenterStackWidget->addActionWidget(pAction, pWidget);

	return pAction;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	/*if (event->mimeData()->hasFormat(g_strPictureMimeType)) 
	{
		if (event->source() == this) 
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		} 
		else 
		{
			event->acceptProposedAction();
		}
	} else 
	{
		event->ignore();
	}*/
}

void MainWindow::dropEvent(QDropEvent *event)
{
	/*if (event->mimeData()->hasFormat(g_strPictureMimeType)) 
	{
		QByteArray itemData = event->mimeData()->data(g_strPictureMimeType);
		QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		ModelUnitInfo info;
		dataStream >> info;

		/*QLabel *newIcon = new QLabel(this);
		newIcon->setPixmap(pixmap);
		newIcon->move(event->pos() - offset);
		newIcon->show();
		newIcon->setAttribute(Qt::WA_DeleteOnClose);*1/

		if (event->source() == this) 
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		} else 
		{
			event->acceptProposedAction();
		}
	} 
	else 
	{
		event->ignore();
	}*/
}

void MainWindow::_startLastAction()
{
	if (m_pCenterStackWidget)
	{
		m_pCenterStackWidget->setActionNameWidget(m_strLastAction);
	}
}