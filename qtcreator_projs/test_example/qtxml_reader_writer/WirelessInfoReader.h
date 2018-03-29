#ifndef WIRELESSINFOREADER_H
#define WIRELESSINFOREADER_H

#include <QtCore>

struct stWirelessInfo
{
    QString strNetName;    //网络名称
    QString strType;        //类型
    QStringList listPlatName;   //网络所有的平台名字
};
typedef QList<stWirelessInfo> ListWirelessInfo;

class WirelessInfoReader : public QObject
{
    Q_OBJECT
public:
    explicit WirelessInfoReader(QObject *parent = 0);

    bool readFromXMLFile(const QString& strFilePath);

    const ListWirelessInfo& getInfos()const{return m_listWirelessInfo;}
private:
    ListWirelessInfo    m_listWirelessInfo;
};

#endif // WIRELESSINFOREADER_H
