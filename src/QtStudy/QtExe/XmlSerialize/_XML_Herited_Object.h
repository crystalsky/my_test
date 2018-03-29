#ifndef _H__XML_HERITED_OBJECT_H_
#define _H__XML_HERITED_OBJECT_H_

#include "_XML_Element_Object.h"

//ºÃ≥–∂‘œÛ
struct XML_Herited_Object : public XML_Element_Object
{
	XML_Element_Object elementObj;
public:
	virtual CXmlElement* XmlSerialize(XmlSerialize::XmlSerializerBase* pXmlSerializer,tinyxml2::XMLElement* pParentElement = NULL,
		const char* szLocalElementName = NULL);
};

#endif //_H__XML_HERITED_OBJECT_H_