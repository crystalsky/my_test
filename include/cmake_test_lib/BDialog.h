#ifndef BDialog_h__
#define BDialog_h__

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
	class BDialog;
}

class cmake_test_lib_EXPORT BDialog : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	BDialog(QDialog* parent = NULL);
	~BDialog();

public:
	
protected slots:
		
protected:

private:
	Ui::BDialog* m_pUI;
};

#endif // BDialog_h__
