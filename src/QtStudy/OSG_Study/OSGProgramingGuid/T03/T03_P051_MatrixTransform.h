#ifndef T03_P051_MatrixTransform_h__
#define T03_P051_MatrixTransform_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <osg/Node>
#include "OSGBaseDef.h"
class T03_P051_MatrixTransform : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T03_P051_MatrixTransform)
public:
	T03_P051_MatrixTransform();
	~T03_P051_MatrixTransform();

public:
	osg::Node* getNode();
protected:
	
private:

};

#endif // T03_P051_MatrixTransform_h__
