#include <QApplication>
#include "demo_dialog.h"
#include <iostream>
#include <iosfwd>
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	Demo_Dialog dlg;
    dlg.show();
    int n = app.exec();

	return n;
}
