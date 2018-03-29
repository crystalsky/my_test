#ifndef CQ_h__
#define CQ_h__

#include "cmake_test_lib_Export.h"
#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>

class cmake_test_lib_EXPORT CQ : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CQ(QObject* parent = NULL);
	~CQ();

public:
	
protected slots:
	
protected:
	
private:

};

#endif // CQ_h__
