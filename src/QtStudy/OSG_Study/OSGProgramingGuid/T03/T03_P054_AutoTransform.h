#ifndef T03_P054_AutoTransform_h__
#define T03_P054_AutoTransform_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <osg/Node>
#include "OSGBaseDef.h"
class T03_P054_AutoTransform : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T03_P054_AutoTransform)
public:
	T03_P054_AutoTransform();
	~T03_P054_AutoTransform();

public:
	osg::Node* getNode();
protected:
	
private:

};

#endif // T03_P054_AutoTransform_h__
