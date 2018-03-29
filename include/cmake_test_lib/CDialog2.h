#ifndef CDialog2_h__
#define CDialog2_h__

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
	class CDialog2;
}

class cmake_test_lib_Export CDialog2 : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CDialog2(QDialog* parent = NULL);
	~CDialog2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::CDialog2* m_pUI;
};

#endif // CDialog2_h__
