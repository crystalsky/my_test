#ifndef T04_P98_Tessellator_h__
#define T04_P98_Tessellator_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T04_P98_Tessellator : public ReflectedOSGFuncBase
{
    DECLARE_REFLECTED_CLASS(T04_P98_Tessellator)
public:
    T04_P98_Tessellator();
    ~T04_P98_Tessellator();


public:
    virtual osg::Node* getNode();
protected:
    
private:

};

#endif // T04_P98_Tessellator_h__
