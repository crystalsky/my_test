#ifndef ADialogInner2_h__
#define ADialogInner2_h__

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
	class ADialogInner2;
}

class ADialogInner2 : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	ADialogInner2(QDialog* parent = NULL);
	~ADialogInner2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::ADialogInner2* m_pUI;
};

#endif // ADialogInner2_h__
