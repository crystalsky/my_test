
#include <QtWidgets>
#include "mainwindow.h"
#include "QMLStudy/widget_QMLStudy.h"
#include "QtGUIStudy/widget_QtGuiStudy.h"
#include "QtCoreStudy/widget_QtCoreStudy.h"
#include "BoostStudy/boost_test_1.h"
#include "BoostStudy/widget_BoostStudy.h"
#include "QtGUIStudy/PicToolWidget.h"
#include "QtGUIStudy/PictureTableView.h"
#include "OtherTest/EMDataShow/EMDataSelectWidget.h"
#include "OtherTest/EMDataShow/EMDataShow.h"
#include "demo_dialog.h"
//! [0]

//! [1]
MainWindow::MainWindow()
{
	m_pCenterWidget = new QStackedWidget(this);
	setCentralWidget(m_pCenterWidget);

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
	m_pMenu_Stl = menuBar()->addMenu(QStringLiteral("STL"));
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

	PicToolWidget* pWidget = new PicToolWidget(NULL);

	QDockWidget* pDockToolBox = new QDockWidget(QStringLiteral("ToolBox²âÊÔ"), this);
	pDockToolBox->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	customerList = new QListWidget(dock);
	installEventFilter(pWidget);

	pDockToolBox->setWidget(pWidget);
	addDockWidget(Qt::LeftDockWidgetArea, pDockToolBox);
}

void MainWindow::slotAction()
{
	QAction* pAction = qobject_cast<QAction*>(sender());
	if (pAction != NULL)
	{
		m_strLastAction = pAction->objectName();
		if (m_mapFunctionalWidget.contains(pAction))
		{
			m_pCenterWidget->setCurrentWidget(m_mapFunctionalWidget.value(pAction));
		}
	}
}

void MainWindow::_readSetting()
{
	QSettings settings("xStudyx", "QtExt");
	bool b = restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());

	m_strLastAction = settings.value("LastActionName", "NONE").toString();
}

void MainWindow::_saveSetting()
{
	QSettings settings("xStudyx", "QtExt");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());

	QSettings setting(qApp->applicationDirPath() + "/setting.ini", QSettings::IniFormat);
	setting.setIniCodec(QTextCodec::codecForLocale());
	setting.beginGroup(QStringLiteral("µÚÒ»×é"));
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
	{//QtGUI
		{
			QAction* pAction = 
				_addFunctionAction(new CWidget_QMLGui(this), 
				QStringLiteral("Page1"), QIcon(":/images/new.png"));
			pAction->setShortcuts(QKeySequence::New);
			m_pMenu_QtGUI->addAction(pAction);
		}

	}
	{//QML
		{
			QAction* pAction = 
				_addFunctionAction(new CWidget_QMLStudy(this), 
				QStringLiteral("Tutorials"), QIcon(":/images/new.png"));
			pAction->setShortcuts(QKeySequence::New);
			m_pMenu_QML->addAction(pAction);
		}
	}
	{//QtCore
		{
			QAction* pAction = 
				_addFunctionAction(new Study_QtCore::CStudyWidget(this), 
				QStringLiteral("QtConcurunt"), QIcon(":/images/new.png"));
			pAction->setShortcuts(QKeySequence::New);
			m_pMenu_QtCore->addAction(pAction);
		}
	}
	{//Boost
		{
			QAction* pAction = 
				_addFunctionAction(new Study_Boost::CWidget_BoostStudy(this), 
				QStringLiteral("boost_test_1"), QIcon(":/images/new.png"));
			pAction->setShortcuts(QKeySequence::New);
			m_pMenu_Boost->addAction(pAction);
		}
	}
	{//OtherTest
		{
			m_pEMDataShow = new CEMDataShow(this);
			QAction* pAction = 
				_addFunctionAction(new CEMDataSelectWidget(m_pEMDataShow, this), 
				QStringLiteral("EMDataShowTest"), QIcon(":/images/new.png"));
			m_pMenu_OtherTest->addAction(pAction);
		}
		{
			QAction* pAction = 
				_addFunctionAction(new Demo_Dialog(this), 
				QStringLiteral("QtPickColor"), QIcon(":/images/new.png"));
			m_pMenu_OtherTest->addAction(pAction);
		}
	}
}

QAction* MainWindow::_addFunctionAction(QWidget* pWidget, const QString& strActionName, const QIcon& icon)
{
	QAction* pAction = new QAction(icon, strActionName, this);
	pAction->setObjectName(strActionName);
	connect(pAction, SIGNAL(triggered()), SLOT(slotAction()));

	m_mapFunctionalWidget.insert(pAction, pWidget);
	m_pCenterWidget->addWidget(pWidget);

	return pAction;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat(g_strPictureMimeType)) 
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
	}
}

void MainWindow::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat(g_strPictureMimeType)) 
	{
		QByteArray itemData = event->mimeData()->data(g_strPictureMimeType);
		QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		ModelUnitInfo info;
		dataStream >> info;

		/*QLabel *newIcon = new QLabel(this);
		newIcon->setPixmap(pixmap);
		newIcon->move(event->pos() - offset);
		newIcon->show();
		newIcon->setAttribute(Qt::WA_DeleteOnClose);*/

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
	}
}

void MainWindow::_startLastAction()
{
	QMapIterator<QAction*, QWidget*> iter(m_mapFunctionalWidget);
	while (iter.hasNext())
	{
		QAction* pAction = iter.next().key();
		if (pAction->objectName() == m_strLastAction)
		{
			pAction->triggered();
			break;
		}
	}
}