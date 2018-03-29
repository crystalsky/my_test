#ifndef EQ_h__
#define EQ_h__

#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>

class EQ : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	EQ(QObject* parent = NULL);
	~EQ();

public:
	
protected slots:
	
protected:
	
private:

};

#endif // EQ_h__
