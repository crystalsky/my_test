#include "ServerDialog.h"
#include <QApplication>
#include <QDebug>
#include "QU_DebugString.h"
#include "QU_Func.h"
#include "QU_Guid.h"
#include "UIItem_Page.h"
#include <QLibrary>

int main(int argc, char *argv[])
{
	QString strDllPath;

	QApplication a(argc, argv);
    CServerDialog w;
    w.show();

    return a.exec();
}
