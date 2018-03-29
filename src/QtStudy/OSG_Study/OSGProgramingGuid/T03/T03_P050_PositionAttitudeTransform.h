#ifndef T03_P050_PositionAttitudeTransform_h__
#define T03_P050_PositionAttitudeTransform_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "OSGBaseDef.h"

class T03_P050_PositionAttitudeTransform : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T03_P050_PositionAttitudeTransform)
public:
	T03_P050_PositionAttitudeTransform();
	~T03_P050_PositionAttitudeTransform();

public:
	virtual osg::Node* getNode();
protected:
	
private:

};

#endif // T03_P050_PositionAttitudeTransform_h__
