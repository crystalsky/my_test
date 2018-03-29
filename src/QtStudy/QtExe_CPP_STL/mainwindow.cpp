
#include "qt_includes.h"
#include "mainwindow.h"
#include <TTimePrint.h>
#include "CPPStudy/widget_cppstudy_root.h"

#include "STLStudy/_STLTestWidget.h"
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
	m_pMenu_Stl = menuBar()->addMenu(QStringLiteral("STL"));
	m_pMenu_cpp = menuBar()->addMenu(QStringLiteral("CPP"));
	m_pMenu_PatternDesign = menuBar()->addMenu(QStringLiteral("PatternDesign"));
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
	
	{//STL
		QAction* pAction = 
			_addFunctionAction(new _STLTestWidget(this), 
			QStringLiteral("STL_Test"), QIcon(":/images/new.png"));
		//pAction->setShortcuts(QKeySequence::New);
		m_pMenu_Stl->addAction(pAction);
	}
	{//PatternDesign
		QAction* pAction = 
			_addFunctionAction(new cppstudy::widget_cppstudy_root(this), 
			QStringLiteral("cpp_class"), QIcon(":/images/new.png"));
		//pAction->setShortcuts(QKeySequence::New);
		m_pMenu_cpp->addAction(pAction);
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