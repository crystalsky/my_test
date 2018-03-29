#ifndef WIREDNETINFOREADER_H
#define WIREDNETINFOREADER_H

#include <QtCore>

//有线网信息
struct stWiredNetInfo
{
    QString strNetName;
    QString strNetType;
    QStringList listPlatName;
};
typedef QList<stWiredNetInfo> ListWiredNetInfo;

class WiredNetInfoReader : public QObject
{
    Q_OBJECT
public:
    explicit WiredNetInfoReader(QObject *parent = 0);

    bool readFromXMLFile(const QString& strFilePath);

    const ListWiredNetInfo& getInfos()const{return m_listWiredNetInfo;}
signals:

public slots:

private:
    ListWiredNetInfo m_listWiredNetInfo;
};

#endif // WIREDNETINFOREADER_H
