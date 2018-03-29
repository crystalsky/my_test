#ifndef T03_P071_CoordinateSystemNode_h__
#define T03_P071_CoordinateSystemNode_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T03_P071_CoordinateSystemNode : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T03_P071_CoordinateSystemNode)
public:
	T03_P071_CoordinateSystemNode();
	~T03_P071_CoordinateSystemNode();

public:
	virtual osg::Node* getNode();
protected:
	
private:

};

#endif // T03_P071_CoordinateSystemNode_h__
