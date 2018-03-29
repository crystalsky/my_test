#ifndef _STLTestWidget_h__
#define _STLTestWidget_h__

#include "StepBase.h"
#include "ReflectButtonFunctionWidget.h"

class _STLTestWidget : public QtUI::CStepBase
{
	Q_OBJECT
public:
	_STLTestWidget(QWidget* pParnet);
	~_STLTestWidget();
};

class _STLTestWidget_SubWidget : public ReflectButtonFunctionWidget
{
	Q_OBJECT
public:
	_STLTestWidget_SubWidget(QWidget* pParent = NULL);
	~_STLTestWidget_SubWidget(){}

public:
	void init();
private:
	virtual bool onButtonClicked(const QString& strFunctionButtonName);
};


#endif // _test_widget_template_h__
