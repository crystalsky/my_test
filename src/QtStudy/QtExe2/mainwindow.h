#ifndef MainWindow_h__
#define MainWindow_h__

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class myObject : public QObject
{
	Q_OBJECT
public:
	myObject() {}
	~myObject() {}

	public slots:
		void first() 
		{
			qDebug()<< QThread::currentThreadId();
		}
		void second() 
		{
			qDebug()<< QThread::currentThreadId();
		}
		void third() 
		{
			qDebug()<< QThread::currentThreadId();
		}
};

class MainWindow : public QMainWindow
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	explicit MainWindow(QWidget * parent = 0, Qt::WindowFlags f = 0);
	~MainWindow();

public:
	

	public slots:
		void onFirstPushed();
		void onSelfPushed();
		void onPMY();
protected:
	myObject *my;
	QPushButton *firstButton,*secondButton,*thirdButton,*selfButton;
private:

};

#endif // MainWindow_h__
