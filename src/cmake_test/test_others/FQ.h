#ifndef FQ_h__
#define FQ_h__

#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>

class FQ : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	FQ(QObject* parent = NULL);
	~FQ();

public:
	
protected slots:
	
protected:
	
private:

};

#endif // FQ_h__
