#include "widget_cppstudy_root.h"
#include "cppstudy_widget_1.h"
namespace cppstudy
{
	widget_cppstudy_root::widget_cppstudy_root( QWidget* pParnet )
		: QtUI::CStepBase(pParnet)
	{
		//TODO:add the childwidgt use addFunctionalWidget
		addFunctionalWidget("cpp_class", new cppstudy_widget_1(this));
	}

	widget_cppstudy_root::~widget_cppstudy_root()
	{

	}
}
