#include <QCoreApplication>
#include "wirednetinforeader.h"
#include "WirelessInfoReader.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WiredNetInfoReader reader;

    const QString& strFilePath =
            QCoreApplication::applicationDirPath()
            + "/../data/BusinessConfigResult.xml";
    if(!reader.readFromXMLFile(strFilePath))
    {

    }


    WirelessInfoReader readerWireless;
    const QString& strFilePath1 =
            QCoreApplication::applicationDirPath()
            + "/../data/DLScenario.xml";
    readerWireless.readFromXMLFile(strFilePath1);

    return a.exec();
}
