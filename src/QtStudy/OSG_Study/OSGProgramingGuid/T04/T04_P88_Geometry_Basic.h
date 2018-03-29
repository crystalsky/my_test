#ifndef T04_P88_Geometry_Basic_h__
#define T04_P88_Geometry_Basic_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T04_P88_Geometry_Basic : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T04_P88_Geometry_Basic)
public:
	T04_P88_Geometry_Basic();
	~T04_P88_Geometry_Basic();


public:
	virtual osg::Node* getNode();
protected:
	
private:

};

#endif // T04_P88_Geometry_Basic_h__
