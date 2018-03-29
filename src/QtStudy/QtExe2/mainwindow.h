#ifndef MainWindow_h__
#define MainWindow_h__

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	explicit MainWindow(QWidget * parent = 0, Qt::WindowFlags f = 0);
	~MainWindow();

public:
	
protected Q_SLOTS:
		
protected:

private:

};

#endif // MainWindow_h__
