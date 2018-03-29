#ifndef AWidget_h__
#define AWidget_h__

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
	class AWidget;
}

class cmake_test_lib_EXPORT AWidget : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	AWidget(QWidget* parent = NULL);
	~AWidget();

public:
	
protected slots:
		
protected:

private:
	Ui::AWidget* m_pUI;
};

#endif // AWidget_h__
