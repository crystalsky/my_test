#ifndef OSGViewerBase_h__
#define OSGViewerBase_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class OSGViewerBase : public ReflectedOSGFuncBase
{
    DECLARE_REFLECTED_CLASS(OSGViewerBase)
public:
    OSGViewerBase();
    ~OSGViewerBase();

    virtual void init();
public:
    virtual osg::Node* getNode();
protected:
    void _doInit();
private:

};

#endif // OSGViewerBase_h__
