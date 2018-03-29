#ifndef CDialogInner2_h__
#define CDialogInner2_h__

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
	class CDialogInner2;
}

class CDialogInner2 : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CDialogInner2(QDialog* parent = NULL);
	~CDialogInner2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::CDialogInner2* m_pUI;
};

#endif // CDialogInner2_h__
