#ifndef OSG_Examples_h__
#define OSG_Examples_h__

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
	class OSG_Examples;
}

class OSG_Examples : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	OSG_Examples(QWidget* parent = NULL);
	~OSG_Examples();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::OSG_Examples* m_pUI;
};

#endif // OSG_Examples_h__
