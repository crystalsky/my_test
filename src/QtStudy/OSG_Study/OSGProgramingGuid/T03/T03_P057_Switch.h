#ifndef T03_P057_Switch_h__
#define T03_P057_Switch_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <osg/Node>
#include "OSGBaseDef.h"

class T03_P057_Switch : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T03_P057_Switch)
public:
	T03_P057_Switch();
	~T03_P057_Switch();

public:
	osg::Node* getNode();
protected:
	
private:

};

#endif // T03_P057_Switch_h__
