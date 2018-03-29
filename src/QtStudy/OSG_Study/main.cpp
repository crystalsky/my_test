#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSharedPointer>
#include <glogInit.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QSharedPointer<glogInit> glog(glogInit::GetInstance());
	glog->init(argv[0]);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
