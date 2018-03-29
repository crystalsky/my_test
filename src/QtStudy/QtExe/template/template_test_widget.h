#ifndef template_test_widget_h__
#define template_test_widget_h__

#include "StepBase.h"
#include "ReflectButtonFunctionWidget.h"

class template_test_widget : public QtUI::CStepBase
{
	Q_OBJECT
public:
	template_test_widget(QWidget* pParnet);
	~template_test_widget();
};

class template_test_widget_SubWidget : public ReflectButtonFunctionWidget
{
	Q_OBJECT
public:
	template_test_widget_SubWidget(QWidget* pParent = NULL);
	~template_test_widget_SubWidget(){}

public:
	void init();
private:
	virtual bool onButtonClicked(const QString& strFunctionButtonName);
};


#endif // _test_widget_template_h__
