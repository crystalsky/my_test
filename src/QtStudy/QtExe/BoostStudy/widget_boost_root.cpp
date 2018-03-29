#include "widget_boost_root.h"
#include "boost_memory_manage.h"

namespace Study_Boost
{
	widget_boost_root::widget_boost_root( QWidget* pParnet )
		: QtUI::CStepBase(pParnet)
	{
		//TODO:add the childwidgt use addFunctionalWidget
		addFunctionalWidget("boost_memory_manage",	
			new boost_memory_manage(this));
	}

	widget_boost_root::~widget_boost_root()
	{

	}
}
