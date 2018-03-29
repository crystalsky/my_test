#ifndef _H_XML_ATTRIBUTE_OBJECT_H_
#define _H_XML_ATTRIBUTE_OBJECT_H_

#include "xml_data_gen_functions.h"

struct XML_Attribute_Object : public XmlSerialize::XmlSerializeObject
{
	xml_data_gen_functions::GenObject val;

	bool operator == (const XML_Attribute_Object& ot)const
	{
		return val == ot.val;
	}
public:
	virtual CXmlElement* XmlSerialize(XmlSerialize::XmlSerializerBase* pXmlSerializer,
		CXmlElement* pParentElement = NULL,
		const char* szLocalElementName = NULL);
};

#endif //_H_XML_ATTRIBUTE_OBJECT_H_
