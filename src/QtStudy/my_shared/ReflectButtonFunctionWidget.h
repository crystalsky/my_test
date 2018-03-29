#ifndef ReflectButtonFunctionWidget_h__
#define ReflectButtonFunctionWidget_h__

#include "StepBase.h"

class ReflectButtonFunctionWidget : public QtUI::CButtonFunctionWidget
{
	Q_OBJECT
public:
	ReflectButtonFunctionWidget(QWidget* pParent = NULL);
	ReflectButtonFunctionWidget(int nColNum, QWidget* pParent = NULL);
	~ReflectButtonFunctionWidget(){}

public:
	void init();
protected:
	virtual bool onButtonClicked(const QString& strFunctionButtonName);
};



#endif // ReflectButtonFunctionWidget_h__
