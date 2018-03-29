#ifndef T04_P105_Delaunay_h__
#define T04_P105_Delaunay_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T04_P105_Delaunay : public ReflectedOSGFuncBase
{
    DECLARE_REFLECTED_CLASS(T04_P105_Delaunay)
public:
    T04_P105_Delaunay();
    ~T04_P105_Delaunay();

    virtual void init();
public:
    virtual osg::Node* getNode();
protected:
    void _doInit();
private:

};

#endif // T04_P105_Delaunay_h__
