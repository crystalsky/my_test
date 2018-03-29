#ifndef Page_QTextCodec_h__
#define Page_QTextCodec_h__

#include "StepBase.h"
#include "ReflectButtonFunctionWidget.h"

class Page_QTextCodec : public QtUI::CStepBase
{
	Q_OBJECT
public:
	Page_QTextCodec(QWidget* pParnet);
	~Page_QTextCodec();
};

class Page_QTextCodec_SubWidget : public ReflectButtonFunctionWidget
{
	Q_OBJECT
public:
	Page_QTextCodec_SubWidget(QWidget* pParent = NULL);
	~Page_QTextCodec_SubWidget(){}

public:
	void init();
private:
	virtual bool onButtonClicked(const QString& strFunctionButtonName);
};


#endif // _test_widget_template_h__
