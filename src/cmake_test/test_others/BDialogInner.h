#ifndef BDialogInner_h__
#define BDialogInner_h__

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
	class BDialogInner;
}

class BDialogInner : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	BDialogInner(QDialog* parent = NULL);
	~BDialogInner();

public:
	
protected slots:
		
protected:

private:
	Ui::BDialogInner* m_pUI;
};

#endif // BDialogInner_h__
