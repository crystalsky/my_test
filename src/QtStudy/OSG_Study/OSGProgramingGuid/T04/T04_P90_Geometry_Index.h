#ifndef T04_P90_Geometry_Index_h__
#define T04_P90_Geometry_Index_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T04_P90_Geometry_Index : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T04_P90_Geometry_Index)
public:
	T04_P90_Geometry_Index();
	~T04_P90_Geometry_Index();

public:
	virtual osg::Node* getNode();
	
protected:
	
private:

};

#endif // T04_P90_Geometry_Index_h__
