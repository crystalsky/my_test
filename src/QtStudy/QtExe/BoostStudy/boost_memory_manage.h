#ifndef boost_memory_manage_h__
#define boost_memory_manage_h__

#include "ReflectButtonFunctionWidget.h"

namespace Study_Boost
{
	class boost_memory_manage : public ReflectButtonFunctionWidget
	{
		Q_OBJECT
	public:
		boost_memory_manage(QWidget* pParent = NULL);
		~boost_memory_manage(){}

	public:
		void init();
	private:
		virtual bool onButtonClicked(const QString& strFunctionButtonName);
	};
}


#endif // _test_widget_template_h__
