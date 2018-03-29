#ifndef DQ_h__
#define DQ_h__

#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>

class DQ : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	DQ(QObject* parent = NULL);
	~DQ();

public:
	
protected slots:
	
protected:
	
private:

};

#endif // DQ_h__
