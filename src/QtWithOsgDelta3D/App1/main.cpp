#include <QApplication>
#include "mainwindow.h"
#include "glogInit.h"
#include <iostream>
#include <iosfwd>
#include "def.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	glogInit::GetInstance()->init(argv[0]);

	LOG(INFO) << "11111:" << g_nVal;
	LOG(INFO) << "22222:" << AAA;

	MainWindow mainWin;
    mainWin.show();
    int n = app.exec();

	glogInit::ExitInstance();

	return n;
}
