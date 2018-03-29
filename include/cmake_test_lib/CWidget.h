#ifndef CWidget_h__
#define CWidget_h__

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
	class CWidget;
}

class cmake_test_lib_EXPORT CWidget : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CWidget(QWidget* parent = NULL);
	~CWidget();

public:
	
protected slots:
		
protected:

private:
	Ui::CWidget* m_pUI;
};

#endif // CWidget_h__
