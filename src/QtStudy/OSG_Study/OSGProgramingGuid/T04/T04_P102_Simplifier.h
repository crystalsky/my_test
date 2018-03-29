#ifndef T04_P102_Simplifier_h__
#define T04_P102_Simplifier_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T04_P102_Simplifier : public ReflectedOSGFuncBase
{
    DECLARE_REFLECTED_CLASS(T04_P102_Simplifier)
public:
    T04_P102_Simplifier();
    ~T04_P102_Simplifier();

    virtual void init();
public:
    virtual osg::Node* getNode();
protected:
    void _doInit();
private:

};

#endif // T04_P102_Simplifier_h__
