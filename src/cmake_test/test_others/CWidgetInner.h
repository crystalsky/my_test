#ifndef CWidgetInner_h__
#define CWidgetInner_h__

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
	class CWidgetInner;
}

class CWidgetInner : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CWidgetInner(QWidget* parent = NULL);
	~CWidgetInner();

public:
	
protected slots:
		
protected:

private:
	Ui::CWidgetInner* m_pUI;
};

#endif // CWidgetInner_h__
