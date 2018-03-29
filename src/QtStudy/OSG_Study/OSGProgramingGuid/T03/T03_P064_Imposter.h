#ifndef T03_P064_Imposter_h__
#define T03_P064_Imposter_h__

#include <string>
#include <vector>
#include <map>
#include <list>

#include "OSGBaseDef.h"

class T03_P064_Imposter : public ReflectedOSGFuncBase
{
	DECLARE_REFLECTED_CLASS(T03_P064_Imposter)
public:
	T03_P064_Imposter();
	~T03_P064_Imposter();

public:
	virtual osg::Node* getNode();
protected:
	
private:

};




#endif // T03_P064_Imposter_h__
