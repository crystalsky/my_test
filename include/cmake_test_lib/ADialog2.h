#ifndef ADialog2_h__
#define ADialog2_h__

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
	class ADialog2;
}

class cmake_test_lib_Export ADialog2 : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	ADialog2(QDialog* parent = NULL);
	~ADialog2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::ADialog2* m_pUI;
};

#endif // ADialog2_h__
