#ifndef _H__XML_ELEMENT_OBJECT_H_
#define _H__XML_ELEMENT_OBJECT_H_

#include "xml_data_gen_functions.h"

struct XML_Element_Object : public XmlSerialize::XmlSerializeObject
{
	xml_data_gen_functions::GenObject val;
public:
	bool operator == (const XML_Element_Object& obj)const
	{
		return val == obj.val;
	}
	virtual CXmlElement* XmlSerialize(XmlSerialize::XmlSerializerBase* pXmlSerializer,CXmlElement* pParentElement = NULL,
		const char* szLocalElementName = NULL);
};

#endif //_H__XML_ELEMENT_OBJECT_H_
