#ifndef BWidget2_h__
#define BWidget2_h__

#include "cmake_test_lib_Export.h"
#include <QWidget>
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
	class BWidget2;
}

class cmake_test_lib_Export BWidget2 : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	BWidget2(QWidget* parent = NULL);
	~BWidget2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::BWidget2* m_pUI;
};

#endif // BWidget2_h__
