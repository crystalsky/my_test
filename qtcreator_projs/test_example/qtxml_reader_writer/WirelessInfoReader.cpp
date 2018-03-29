#include "WirelessInfoReader.h"
#include <QXmlStreamReader>
#include <QFile>

WirelessInfoReader::WirelessInfoReader(QObject *parent)
    : QObject(parent)
{

}


bool WirelessInfoReader::readFromXMLFile(const QString &strFilePath)
{
    QFile file(strFilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "read File " << strFilePath << " Failed...";
        return false;
    }
    m_listWirelessInfo.clear();

    stWirelessInfo objWiredNetInfo;
    bool bFindSubnet = false;
    QXmlStreamReader reader(&file);
    while (!reader.atEnd())
    {
        QXmlStreamReader::TokenType t= reader.readNext();

        if(reader.isStartElement())
        {
            const QStringRef& strname = reader.name();
            if (strname == "Subnet")
            {
                objWiredNetInfo.strType = reader.attributes()
                        .value("type").toString();
                objWiredNetInfo.strNetName = reader.attributes()
                        .value("name").toString();

                bFindSubnet = true;

                qDebug() << objWiredNetInfo.strType << ","
                         << objWiredNetInfo.strNetName;
            }
            else if(strname == "Module" && bFindSubnet)
            {
                objWiredNetInfo.listPlatName << reader.attributes()
                        .value("name").toString();
            }
        }
        else if(reader.isEndElement())
        {
            const QStringRef& strname = reader.name();
            if (strname == "Subnet")
            {
                bFindSubnet = false;

                m_listWirelessInfo << objWiredNetInfo;
                objWiredNetInfo.listPlatName.clear();
            }
        }
    }

    if (reader.hasError())
    {
        qDebug() << "reader error!!" << reader.errorString();
        return false;
    }

    return !m_listWirelessInfo.isEmpty();
}
