#ifndef BWidgetInner2_h__
#define BWidgetInner2_h__

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
	class BWidgetInner2;
}

class BWidgetInner2 : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	BWidgetInner2(QWidget* parent = NULL);
	~BWidgetInner2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::BWidgetInner2* m_pUI;
};

#endif // BWidgetInner2_h__
