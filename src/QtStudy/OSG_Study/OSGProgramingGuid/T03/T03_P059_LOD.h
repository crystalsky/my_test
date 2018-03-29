#ifndef T03_P059_LOD_h__
#define T03_P059_LOD_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <osg/Node>
#include "OSGBaseDef.h"

class T03_P059_LOD : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T03_P059_LOD)
public:
	T03_P059_LOD();
	~T03_P059_LOD();

public:
	virtual osg::Node* getNode();
protected:

private:

};

#endif // T03_P059_LOD_h__
