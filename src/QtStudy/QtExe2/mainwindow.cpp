#include "MainWindow.h"

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags f)
	: QMainWindow(parent, f)
{
	//setWindowFlags(Qt::FramelessWindowHint);
	//menuBar()->setNativeMenuBar(true);
	setGeometry(100, 100, 500, 500);
	QMenu* pMenu = menuBar()->addMenu("Test");

	QDockWidget* pDock = new QDockWidget();
	this->addDockWidget(Qt::LeftDockWidgetArea,pDock);
	
	pMenu->addAction("test1");
}

MainWindow::~MainWindow()
{
	
}

