#ifndef BWidget_h__
#define BWidget_h__

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
	class BWidget;
}

class cmake_test_lib_EXPORT BWidget : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	BWidget(QWidget* parent = NULL);
	~BWidget();

public:
	
protected slots:
		
protected:

private:
	Ui::BWidget* m_pUI;
};

#endif // BWidget_h__
