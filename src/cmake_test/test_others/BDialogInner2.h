#ifndef BDialogInner2_h__
#define BDialogInner2_h__

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
	class BDialogInner2;
}

class BDialogInner2 : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	BDialogInner2(QDialog* parent = NULL);
	~BDialogInner2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::BDialogInner2* m_pUI;
};

#endif // BDialogInner2_h__
