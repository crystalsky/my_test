#include "MainWindow.h"
#include <boost/thread.hpp>
#include <boost/dynamic_bitset.hpp>

class WaitAck : public boost::noncopyable
{
	mutable boost::mutex the_mutex;  
	boost::condition_variable the_condition_variable; 

public:
	explicit WaitAck() {}
	~WaitAck() {}

	void notify()
	{
		the_condition_variable.notify_one(); 
	}

	bool wait(int nTimeOUt)
	{
		//while(1)   
		{  
			boost::mutex::scoped_lock lock(the_mutex);  
			if (the_condition_variable.timed_wait(lock, 
				boost::get_system_time() + boost::posix_time::millisec(nTimeOUt)))   
			{  
				return true; 
			}   
		}  
		return false;
	}
};

QSemaphore se;
WaitAck ack;
class NewThread : public QThread
{
public:
	NewThread()
	{

	}

	void run()
	{
		while(1)
		{
			QThread::msleep(1000);
			ack.notify();
		}
	}
};

NewThread nt;


void delaymsec(int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);

	while( QTime::currentTime() < dieTime)
	{
// 		if (se.tryAcquire(1, 50))
// 		{
// 			qDebug() << "get value";
// 		}
		if(ack.wait(50))
		{
			qDebug() << "get value";
		}

		QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
	}
}

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags f)
	: QMainWindow(parent, f)
{
	my = new myObject;



	QWidget* pNewWidget = new QWidget(this);
	setCentralWidget(pNewWidget);

	firstButton = new QPushButton(tr("firstBtn"), pNewWidget);
	connect(firstButton, SIGNAL(clicked()), this, SLOT(onFirstPushed()));
	secondButton = new QPushButton(tr("secondBtn"), pNewWidget);
	connect(secondButton, SIGNAL(clicked()), my, SLOT(second()), Qt::DirectConnection);
	thirdButton = new QPushButton(tr("thirdBtn"), pNewWidget);
	connect(thirdButton, SIGNAL(clicked()), my, SLOT(third()), Qt::QueuedConnection);
	selfButton = new QPushButton(tr("selfBtn"), pNewWidget);
	connect(selfButton, SIGNAL(clicked()), this, SLOT(onSelfPushed()));

	QPushButton* pMy = new QPushButton(tr("pMy"), pNewWidget);
	connect(pMy, SIGNAL(clicked()), this, SLOT(onPMY()));

	QLayout *layout = new QVBoxLayout();
	layout->addWidget(firstButton);
	layout->addWidget(secondButton);
	layout->addWidget(thirdButton);
	layout->addWidget(selfButton);
	pNewWidget->setLayout(layout);

	QThread *thread = new QThread;
	my->moveToThread(thread);
	connect(thread, SIGNAL(started()), my, SLOT(first()));
	thread->start();

	//setWindowFlags(Qt::FramelessWindowHint);
	//menuBar()->setNativeMenuBar(true);
	setGeometry(100, 100, 500, 500);
	QMenu* pMenu = menuBar()->addMenu("Test");

	QDockWidget* pDock = new QDockWidget();
	this->addDockWidget(Qt::LeftDockWidgetArea,pDock);
	
	QAction* p = pMenu->addAction("test1");

	//delaymsec(10000);
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::onFirstPushed() 
{
	my->first();
}

void MainWindow::onSelfPushed() 
{
	qDebug() << QThread::currentThreadId();
}

void MainWindow::onPMY()
{
	nt.start();
	delaymsec(10000);
}

