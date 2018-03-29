#include <QApplication>
#include "mainwindow.h"
#include "glogInit.h"
#include <iostream>
#include <iosfwd>
#include "def.h"
#include <QRegExp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	glogInit::GetInstance()->init(argv[0]);

	MainWindow mainWin;
    mainWin.show();
    int n = app.exec();

	glogInit::ExitInstance();

	return n;
}
