#ifndef OSG_DesignAndPractice_h__
#define OSG_DesignAndPractice_h__

#include <QWidget>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>
#include <QTabWidget>
#include <QHBoxLayout>
#include "osgviewerQt.h"
#include "CFunctionOSGViewerWidget.h"

class C1 : public CFunctionOSGViewerWidget
{
	Q_OBJECT
public:
	C1(QWidget* pParnet);
	~C1();

public:

protected Q_SLOTS:
	virtual void slotButtonClicked(const QString& strFunctionButtonName);
};



class OSG_DesignAndPractice : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	OSG_DesignAndPractice(QWidget* parent = NULL);
	~OSG_DesignAndPractice();

public:
	
protected slots:
	
protected:
	
private:
	QTabWidget* m_pTableWidget;
};

#endif // OSG_DesignAndPractice_h__
