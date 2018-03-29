#ifndef OSG_Test_h__
#define OSG_Test_h__

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

namespace Ui 
{
	class OSG_Test;
}

class OSG_Test : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	OSG_Test(QWidget* parent = NULL);
	~OSG_Test();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::OSG_Test* m_pUI;
};

#endif // OSG_Test_h__
