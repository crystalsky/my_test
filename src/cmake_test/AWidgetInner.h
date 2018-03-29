#ifndef AWidgetInner_h__
#define AWidgetInner_h__

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
	class AWidgetInner;
}

class AWidgetInner : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	AWidgetInner(QWidget* parent = NULL);
	~AWidgetInner();

public:
	
protected slots:
		
protected:

private:
	Ui::AWidgetInner* m_pUI;
};

#endif // AWidgetInner_h__
