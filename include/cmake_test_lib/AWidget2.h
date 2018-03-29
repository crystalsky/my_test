#ifndef AWidget2_h__
#define AWidget2_h__

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
	class AWidget2;
}

class cmake_test_lib_Export AWidget2 : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	AWidget2(QWidget* parent = NULL);
	~AWidget2();

public:
	
protected Q_SLOTS:
		
protected:

private:
	Ui::AWidget2* m_pUI;
};

#endif // AWidget2_h__
