#ifndef cppstudy_widget_1_h__
#define cppstudy_widget_1_h__

#include "ReflectButtonFunctionWidget.h"

namespace cppstudy
{
	class cppstudy_widget_1 : public ReflectButtonFunctionWidget
	{
		Q_OBJECT
	public:
		cppstudy_widget_1(QWidget* pParent = NULL);
		~cppstudy_widget_1(){}

	public:
		void init();
	private:
		virtual bool onButtonClicked(const QString& strFunctionButtonName);
	};
}


#endif // _test_widget_template_h__
