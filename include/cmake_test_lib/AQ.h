#ifndef AQ_h__
#define AQ_h__

#include "cmake_test_lib_Export.h"
#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>

class cmake_test_lib_EXPORT AQ : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	AQ(QObject* parent = NULL);
	~AQ();

public:
	
protected slots:
	
protected:
	
private:

};

#endif // AQ_h__
