#ifndef AQ2_h__
#define AQ2_h__

#include "cmake_test_lib_Export.h"
#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>

class cmake_test_lib_Export AQ2 : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	AQ2(QObject* parent = NULL);
	~AQ2();

public:
	
protected Q_SLOTS:
	
protected:
	
private:

};

#endif // AQ2_h__
