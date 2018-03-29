#ifndef ChartDrawManager_h__
#define ChartDrawManager_h__

#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>

class ChartDrawManager : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	ChartDrawManager(QObject* parent = NULL);
	~ChartDrawManager();

public:
	
protected Q_SLOTS:
	
protected:
	
private:

};

#endif // ChartDrawManager_h__
