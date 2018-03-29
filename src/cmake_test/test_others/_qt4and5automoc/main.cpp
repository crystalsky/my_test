#include <QObject>
#include "ADialogInner.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char **argv)
{
	  QApplication app(argc, argv);

	QMainWindow dlg;
	dlg.show();

	app.exec();
  return 0;
}
