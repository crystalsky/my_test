#ifndef T04_P112_SmoothingVisitor_h__
#define T04_P112_SmoothingVisitor_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T04_P112_SmoothingVisitor : public ReflectedOSGFuncBase
{
    DECLARE_REFLECTED_CLASS(T04_P112_SmoothingVisitor)
public:
    T04_P112_SmoothingVisitor();
    ~T04_P112_SmoothingVisitor();

    virtual void init();
public:
    virtual osg::Node* getNode();
protected:
    void _doInit();
private:

};

#endif // T04_P112_SmoothingVisitor_h__
