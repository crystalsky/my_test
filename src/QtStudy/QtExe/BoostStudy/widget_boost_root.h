#ifndef widget_boost_root_h__
#define widget_boost_root_h__

#include "StepBase.h"

namespace Study_Boost
{
    class widget_boost_root : public QtUI::CStepBase
    {
        Q_OBJECT
    public:
        widget_boost_root(QWidget* pParnet);
        ~widget_boost_root();
    };
}

#endif // _test_widget_template_h__
