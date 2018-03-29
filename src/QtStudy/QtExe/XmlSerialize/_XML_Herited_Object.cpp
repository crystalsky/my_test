#include "_XML_Herited_Object.h"

CXmlElement* XML_Herited_Object::XmlSerialize( XmlSerialize::XmlSerializerBase* pXmlSerializer,tinyxml2::XMLElement* pParentElement /*= NULL*/, const char* szLocalElementName /*= NULL*/ )
{
	BEGIN_XML_SERIALIZE_BASE(XML_Herited_Object, XML_Element_Object)
		XML_SERIALIZE_OBJECT_TVAR(elementObj)
	END_XML_SERIALIZE()
}