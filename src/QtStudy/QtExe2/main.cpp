#include <QApplication>
#include "mainwindow.h"
#include <iostream>
#include <iosfwd>
#include <QRegExp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	MainWindow mainWin;
    mainWin.show();
    int n = app.exec();


	return n;
}
