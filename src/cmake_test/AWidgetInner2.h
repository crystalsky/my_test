#ifndef AWidgetInner2_h__
#define AWidgetInner2_h__

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
	class AWidgetInner2;
}

class AWidgetInner2 : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	AWidgetInner2(QWidget* parent = NULL);
	~AWidgetInner2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::AWidgetInner2* m_pUI;
};

#endif // AWidgetInner2_h__
