#ifndef XmlSerialize_Test_Widget_h__
#define XmlSerialize_Test_Widget_h__

#include "StepBase.h"
#include "ReflectButtonFunctionWidget.h"

class XmlSerialize_Test_Widget : public QtUI::CStepBase
{
	Q_OBJECT
public:
	XmlSerialize_Test_Widget(QWidget* pParnet);
	~XmlSerialize_Test_Widget();
};

class XmlSerialize_Test_Widget_SubWidget : public ReflectButtonFunctionWidget
{
	Q_OBJECT
public:
	XmlSerialize_Test_Widget_SubWidget(QWidget* pParent = NULL);
	~XmlSerialize_Test_Widget_SubWidget(){}

public:
	void init();
private:
	virtual bool onButtonClicked(const QString& strFunctionButtonName);
};


#endif // _test_widget_template_h__
