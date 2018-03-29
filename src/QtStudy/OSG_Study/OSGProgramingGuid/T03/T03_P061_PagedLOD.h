#ifndef T03_P061_PagedLOD_h__
#define T03_P061_PagedLOD_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <osg/Node>
#include "OSGBaseDef.h"

class T03_P061_PagedLOD : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T03_P061_PagedLOD)
public:
	T03_P061_PagedLOD();
	~T03_P061_PagedLOD();

public:
	virtual osg::Node* getNode();
protected:
	
private:

};

#endif // T03_P061_PagedLOD_h__
