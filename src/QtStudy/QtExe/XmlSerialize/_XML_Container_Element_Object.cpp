#include "_XML_Container_Element_Object.h"

//////////////////////////////////////////////////////////////////////////
XML_Container_Element_Object::XML_Container_Element_Object( int nSize /*= 1*/ )
{
	if (nSize < 1)
	{
		nSize = 1;
	}

	for (int i = 0; i < nSize; ++i)
	{
		m_vecIntValues.push_back(xml_data_gen_functions::genInt());
		m_lstIntValues.push_back(xml_data_gen_functions::genInt());
		m_vecDoubleValues.push_back(xml_data_gen_functions::genDouble());
		m_lstDoubleValues.push_back(xml_data_gen_functions::genDouble());

#ifdef XMLSERIALIZE_QT_SUPPORT
		QString strTemp;
		xml_data_gen_functions::genString(strTemp, xml_data_gen_functions::genBool());
		m_lstString.push_back(strTemp);

		xml_data_gen_functions::genString(strTemp, xml_data_gen_functions::genBool());
		m_vecString.push_back(strTemp);
#else
		std::string strTemp;
		xml_data_gen_functions::genString(strTemp, xml_data_gen_functions::genBool());
		m_lstString.push_back(strTemp);

		xml_data_gen_functions::genString(strTemp, xml_data_gen_functions::genBool());
		m_vecString.push_back(strTemp);
#endif
	}
}

tinyxml2::XMLElement* XML_Container_Element_Object::XmlSerialize( XmlSerialize::XmlSerializerBase* pXmlSerializer,
																 CXmlElement* pParentElement /*= NULL*/, 
																 const char* szLocalElementName /*= NULL*/ )
{
	BEGIN_XML_SERIALIZE(XML_Container_Element_Object)
		XML_SERIALIZE_CONTAINER_ELEMENT_TVAR(IntVecItems, IntValue, m_vecIntValues)
		XML_SERIALIZE_CONTAINER_ELEMENT_TVAR(IntListItems, IntValue, m_lstIntValues)
		XML_SERIALIZE_CONTAINER_ELEMENT_TVAR(DoubleVecItems, DoubleValue, m_vecDoubleValues)
		XML_SERIALIZE_CONTAINER_ELEMENT_TVAR(DoubleListItems, DoubleValue, m_lstDoubleValues)
		XML_SERIALIZE_CONTAINER_ELEMENT_TVAR(StringListItems, StringValue, m_lstString)
		XML_SERIALIZE_CONTAINER_ELEMENT_TVAR(StringVecItems, StringValue, m_vecString)
	END_XML_SERIALIZE()
}

