#ifndef T04_P108_TriStripVisitor_h__
#define T04_P108_TriStripVisitor_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T04_P108_TriStripVisitor : public ReflectedOSGFuncBase
{
    DECLARE_REFLECTED_CLASS(T04_P108_TriStripVisitor)
public:
    T04_P108_TriStripVisitor();
    ~T04_P108_TriStripVisitor();

    virtual void init();
public:
    virtual osg::Node* getNode();
protected:
    void _doInit();
private:

};

#endif // T04_P108_TriStripVisitor_h__
