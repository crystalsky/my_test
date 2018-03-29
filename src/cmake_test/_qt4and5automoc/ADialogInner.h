#ifndef ADialogInner_h__
#define ADialogInner_h__

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
	class ADialogInner;
}

class ADialogInner : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	ADialogInner(QDialog* parent = NULL);
	~ADialogInner();

public:
	
protected slots:
		
protected:

private:
	Ui::ADialogInner* m_pUI;
};

#endif // ADialogInner_h__
