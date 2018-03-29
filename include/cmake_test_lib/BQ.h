#ifndef BQ_h__
#define BQ_h__

#include "cmake_test_lib_Export.h"
#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>

class cmake_test_lib_EXPORT BQ : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	BQ(QObject* parent = NULL);
	~BQ();

public:
	
protected slots:
	
protected:
	
private:

};

#endif // BQ_h__
