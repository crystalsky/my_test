#ifndef T03_P067_OccluderNode_h__
#define T03_P067_OccluderNode_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T03_P067_OccluderNode : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T03_P067_OccluderNode)
public:
	T03_P067_OccluderNode();
	~T03_P067_OccluderNode();

public:
	virtual osg::Node* getNode();
protected:
	
private:

};

#endif // T03_P067_OccluderNode_h__
