#ifndef Sub_A_DialogInner_1_h__
#define Sub_A_DialogInner_1_h__

#include <QDialog>
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
	class Sub_A_DialogInner_1;
}

class Sub_A_DialogInner_1 : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	Sub_A_DialogInner_1(QDialog* parent = NULL);
	~Sub_A_DialogInner_1();

public:
	
protected slots:
		
protected:

private:
	Ui::Sub_A_DialogInner_1* m_pUI;
};

#endif // Sub_A_DialogInner_1_h__
