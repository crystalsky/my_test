#ifndef BWidgetInner_h__
#define BWidgetInner_h__

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
	class BWidgetInner;
}

class BWidgetInner : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	BWidgetInner(QWidget* parent = NULL);
	~BWidgetInner();

public:
	
protected slots:
		
protected:

private:
	Ui::BWidgetInner* m_pUI;
};

#endif // BWidgetInner_h__
