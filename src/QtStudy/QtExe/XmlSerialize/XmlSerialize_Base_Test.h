#ifndef XmlSerialize_Base_Test_h__
#define XmlSerialize_Base_Test_h__

#include "Base.h"

class XmlSerialize_Base_Test : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(XmlSerialize_Base_Test)
public:
	XmlSerialize_Base_Test();
	~XmlSerialize_Base_Test();

public:
	virtual void run();
protected:
	
private:

};

#endif // XmlSerialize_Base_Test_h__
