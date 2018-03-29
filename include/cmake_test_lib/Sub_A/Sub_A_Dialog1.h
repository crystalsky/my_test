#ifndef Sub_A_Dialog1_h__
#define Sub_A_Dialog1_h__

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
	class Sub_A_Dialog1;
}

class cmake_test_lib_Export Sub_A_Dialog1 : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	Sub_A_Dialog1(QDialog* parent = NULL);
	~Sub_A_Dialog1();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::Sub_A_Dialog1* m_pUI;
};

#endif // Sub_A_Dialog1_h__
