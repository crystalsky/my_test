#ifndef CWidgetInner2_h__
#define CWidgetInner2_h__

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
	class CWidgetInner2;
}

class CWidgetInner2 : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CWidgetInner2(QWidget* parent = NULL);
	~CWidgetInner2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::CWidgetInner2* m_pUI;
};

#endif // CWidgetInner2_h__
