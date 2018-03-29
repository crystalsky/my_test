#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include "OSGProgramingGuid/T03.h"
#include "OSGProgramingGuid/T04.h"
#include "OSGProgramingGuid/T05.h"
#define TITLE "OSG Home"
#define XMLNodeVariable(name) int n_##name##_Val;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
	, m_pMenu_OSGProgramingGuid(NULL)
{
    ui->setupUi(this);
	setWindowTitle(TITLE);

	//! [1]
	m_pCenterActionStackWidget = new CenterActionStackWidget(this);
	setCentralWidget(m_pCenterActionStackWidget);
	setMinimumSize(800, 600);
	connect(m_pCenterActionStackWidget, SIGNAL(actionTriggered(QAction*)), SLOT(slotActionTriggered(QAction*)));
	
	//! [2]
	_createMenu();
	_createMenuActions();

	//! [3]
	_readSetting();

	//! [4]
	m_pCenterActionStackWidget->setActionNameWidget(m_strLastAction);


	//...................
	XMLNodeVariable(AA)
	n_AA_Val;
	n_AA_Val;
	n_AA_Val;
	n_AA_Val = 0;
	n_AA_Val++;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
	_saveSetting();

	QMainWindow::closeEvent(e);
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
	settings.setValue("LastActionName", m_strLastAction);
}

void MainWindow::_createMenu()
{
	m_pMenu_OSGBooks = menuBar()->addMenu(QStringLiteral("OSG Boos"));
	
	{
		m_pMenu_OSGProgramingGuid = m_pMenu_OSGBooks->addMenu("OSGProgramingGuid");
	}

}

void MainWindow::_createMenuActions()
{
	{//OSG_ProgramingGuid
		_addActionToMenu(
			m_pCenterActionStackWidget->addActionWidget(
			new OSG_ProgramingGuid::T03, "T03"), 
			m_pMenu_OSGProgramingGuid);
		_addActionToMenu(
			m_pCenterActionStackWidget->addActionWidget(
			new OSG_ProgramingGuid::T04, "T04"), 
			m_pMenu_OSGProgramingGuid);
		_addActionToMenu(
			m_pCenterActionStackWidget->addActionWidget(
			new OSG_ProgramingGuid::T05, "T05"), 
			m_pMenu_OSGProgramingGuid);
	}
}

bool MainWindow::_addActionToMenu( QAction* pAction, QMenu* pMenu )
{
	if (pAction != NULL && pMenu != NULL)
	{
		pMenu->addAction(pAction);
	}
	return false;
}

void MainWindow::slotActionTriggered( QAction* pAction )
{
	if (pAction == NULL)
	{
		return;
	}

	m_strLastAction = pAction->objectName();

	QStringList listMenuActions = QStringList() << pAction->objectName();

	QMenu* pMenu = pAction->menu();
	while (pMenu)
	{
		listMenuActions << pMenu->title();
		pMenu = pMenu->menuAction()->menu();
	}

	QString strTitle;
}



