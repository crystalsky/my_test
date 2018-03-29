#ifndef xerces_test_widget_h__
#define xerces_test_widget_h__

#include "StepBase.h"
#include "ReflectButtonFunctionWidget.h"

class xerces_test_widget : public QtUI::CStepBase
{
	Q_OBJECT
public:
	xerces_test_widget(QWidget* pParnet);
	~xerces_test_widget();
};

class xerces_test_widget_SubWidget : public ReflectButtonFunctionWidget
{
	Q_OBJECT
public:
	xerces_test_widget_SubWidget(QWidget* pParent = NULL);
	~xerces_test_widget_SubWidget(){}

public:
	void init();
private:
	virtual bool onButtonClicked(const QString& strFunctionButtonName);
};


#endif // _test_widget_template_h__
