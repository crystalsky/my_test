#ifndef T04_P95_ShapeDrawable_h__
#define T04_P95_ShapeDrawable_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T04_P95_ShapeDrawable : public ReflectedOSGFuncBase
{
    DECLARE_REFLECTED_CLASS(T04_P95_ShapeDrawable)
public:
    T04_P95_ShapeDrawable();
    ~T04_P95_ShapeDrawable();


public:
    virtual osg::Node* getNode();
protected:
    
private:

};

#endif // T04_P95_ShapeDrawable_h__
