#ifndef CWidget2_h__
#define CWidget2_h__

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
	class CWidget2;
}

class cmake_test_lib_Export CWidget2 : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CWidget2(QWidget* parent = NULL);
	~CWidget2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::CWidget2* m_pUI;
};

#endif // CWidget2_h__
