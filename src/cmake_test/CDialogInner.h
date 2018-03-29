#ifndef CDialogInner_h__
#define CDialogInner_h__

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
	class CDialogInner;
}

class CDialogInner : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CDialogInner(QDialog* parent = NULL);
	~CDialogInner();

public:
	
protected slots:
		
protected:

private:
	Ui::CDialogInner* m_pUI;
};

#endif // CDialogInner_h__
