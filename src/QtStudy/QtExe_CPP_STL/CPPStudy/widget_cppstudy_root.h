#ifndef widget_cppstudy_root_h__
#define widget_cppstudy_root_h__

#include "StepBase.h"

namespace cppstudy
{
    class widget_cppstudy_root : public QtUI::CStepBase
    {
        Q_OBJECT
    public:
        widget_cppstudy_root(QWidget* pParnet);
        ~widget_cppstudy_root();
    };
}

#endif // _test_widget_template_h__
