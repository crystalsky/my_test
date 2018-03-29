#ifndef T05_P119_ClipNode_h__
#define T05_P119_ClipNode_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T05_P119_ClipNode : public ReflectedOSGFuncBase
{
    DECLARE_REFLECTED_CLASS(T05_P119_ClipNode)
public:
    T05_P119_ClipNode();
    ~T05_P119_ClipNode();

    virtual void init();
public:
    virtual osg::Node* getNode();
protected:
    void _doInit();
private:

};

#endif // T05_P119_ClipNode_h__
