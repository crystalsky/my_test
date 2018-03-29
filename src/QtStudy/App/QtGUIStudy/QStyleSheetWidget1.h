#ifndef QStyleSheetWidget1_h__
#define QStyleSheetWidget1_h__

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
	class QStyleSheetWidget1;
}
class QStyleSheetWidget1 : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	QStyleSheetWidget1(QWidget* parent = NULL);
	~QStyleSheetWidget1();

public:
	
protected slots:
		
protected:

private:
	Ui::QStyleSheetWidget1* m_pUI;
};

#endif // QStyleSheetWidget1_h__
