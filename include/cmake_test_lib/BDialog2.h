#ifndef BDialog2_h__
#define BDialog2_h__

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
	class BDialog2;
}

class cmake_test_lib_Export BDialog2 : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	BDialog2(QDialog* parent = NULL);
	~BDialog2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::BDialog2* m_pUI;
};

#endif // BDialog2_h__
