#ifndef ADialog_h__
#define ADialog_h__

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
	class ADialog;
}

class cmake_test_lib_EXPORT ADialog : public QDialog
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	ADialog(QDialog* parent = NULL);
	~ADialog();

public:
	
protected slots:
		
protected:

private:
	Ui::ADialog* m_pUI;
};

#endif // ADialog_h__
