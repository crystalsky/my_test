#include "_XML_Container_Object.h"

XML_Container_Object::XML_Container_Object(int nSize, bool flowSize)
{
	if (nSize < 1)
	{
		nSize = 1;
	}
	for (int i = 0; i < nSize; ++i)
	{
		m_vecXmlObject.push_back(XML_Container_Element_Object(flowSize ? i : 1));
		m_listXMLObject.push_back(XML_Container_Element_Object(flowSize ? i : 1));

		m_vecXmlObjectPtr.push_back(new XML_Container_Element_Object(flowSize ? i : 1));
		m_listXMLObjectPtr.push_back(new XML_Container_Element_Object(flowSize ? i : 1));
#ifdef XMLSERIALIZE_SHARED_PTR_SUPPORT
		m_vecXmlObjectSharedPtr.push_back(SharedPtr<XML_Container_Element_Object>(new XML_Container_Element_Object(flowSize ? i : 1)));
		m_listXMLObjectSharedPtr.push_back(SharedPtr<XML_Container_Element_Object>(new XML_Container_Element_Object(flowSize ? i : 1)));
#endif
	}
}

XML_Container_Object::~XML_Container_Object()
{

}

CXmlElement* XML_Container_Object::XmlSerialize( XmlSerialize::XmlSerializerBase* pXmlSerializer,tinyxml2::XMLElement* pParentElement /*= NULL*/, const char* szLocalElementName /*= NULL*/ )
{
	BEGIN_XML_SERIALIZE(XML_Container_Object)
		XML_SERIALIZE_CONTAINER_OBJECT(VectorXML_Container_Element_Object, XML_Container_Element_Object, m_vecXmlObject)
		XML_SERIALIZE_CONTAINER_OBJECT(ListXML_Container_Element_Object, XML_Container_Element_Object, m_listXMLObject)
		XML_SERIALIZE_CONTAINER_OBJECT(VectorXML_Container_Element_ObjectPtr, XML_Container_Element_Object, m_vecXmlObjectPtr)
		XML_SERIALIZE_CONTAINER_OBJECT(ListXML_Container_Element_ObjectPtr, XML_Container_Element_Object, m_listXMLObjectPtr)
#ifdef XMLSERIALIZE_SHARED_PTR_SUPPORT
		XML_SERIALIZE_CONTAINER_OBJECT(VectorXML_Container_Element_SharedPtr_Object, 
			XML_Container_Element_Object, m_vecXmlObjectSharedPtr)
		XML_SERIALIZE_CONTAINER_OBJECT(ListXML_Container_Element_SharedPtr_Object, 
			XML_Container_Element_Object, m_listXMLObjectSharedPtr)
#endif
	END_XML_SERIALIZE()
}

