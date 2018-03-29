#ifndef CDialog_h__
#define CDialog_h__

#include "cmake_test_lib_Export.h"
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
	class CDialog;
}

class cmake_test_lib_EXPORT CDialog : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CDialog(QDialog* parent = NULL);
	~CDialog();

public:
	
protected slots:
		
protected:

private:
	Ui::CDialog* m_pUI;
};

#endif // CDialog_h__
