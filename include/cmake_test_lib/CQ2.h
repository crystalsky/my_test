#ifndef CQ2_h__
#define CQ2_h__

#include "cmake_test_lib_Export.h"
#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>

class cmake_test_lib_Export CQ2 : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CQ2(QObject* parent = NULL);
	~CQ2();

public:
	
protected Q_SLOTS:
	
protected:
	
private:

};

#endif // CQ2_h__
