#include "wirednetinforeader.h"
#include <QXmlStreamReader>
#include <QFile>

WiredNetInfoReader::WiredNetInfoReader(QObject *parent) :
    QObject(parent)
{

}

bool WiredNetInfoReader::readFromXMLFile(const QString &strFilePath)
{
    QFile file(strFilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "read File " << strFilePath << " Failed...";
        return false;
    }
    m_listWiredNetInfo.clear();

    stWiredNetInfo objWiredNetInfo;

    QXmlStreamReader reader(&file);
    while (!reader.atEnd())
    {
        QXmlStreamReader::TokenType t= reader.readNext();

        if(reader.isStartElement())
        {
            const QStringRef& strname = reader.name();
            if (strname == "NetPlat")
            {
                objWiredNetInfo.strNetType = reader.attributes()
                        .value("businessType").toString();
                objWiredNetInfo.strNetName = reader.attributes()
                        .value("name").toString();

                qDebug() << objWiredNetInfo.strNetType << ","
                         << objWiredNetInfo.strNetName;
            }
            else if(strname == "Plat")
            {
                objWiredNetInfo.listPlatName << reader.attributes()
                        .value("name").toString();
            }
        }
        else if(reader.isEndElement())
        {
            const QStringRef& strname = reader.name();
            if (strname == "NetPlat")
            {
                m_listWiredNetInfo << objWiredNetInfo;
                objWiredNetInfo.listPlatName.clear();
            }
        }
    }

    if (reader.hasError())
    {
        qDebug() << "reader error!!" << reader.errorString();
        return false;
    }

    return !m_listWiredNetInfo.isEmpty();
}
