#ifndef widget_OSGStudy_h__
#define widget_OSGStudy_h__

#include <QWidget>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>
#include <QHBoxLayOut>
#include <QVBoxLayOut>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include "StepBase.h"

class widget_OSGStudy : public Study_BaseClass::CTabWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	widget_OSGStudy(QWidget* parent = NULL);
	~widget_OSGStudy();

public:
	
protected slots:
		
protected:

private:

};

#endif // widget_OSGStudy_h__
