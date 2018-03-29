#include "_XML_Element_Object.h"

CXmlElement* XML_Element_Object::XmlSerialize( XmlSerialize::XmlSerializerBase* pXmlSerializer,CXmlElement* pParentElement /*= NULL*/, const char* szLocalElementName /*= NULL*/ )
{
#ifdef XMLSERIALIZE_QT_SUPPORT
	BEGIN_XML_SERIALIZE(XML_Element_Object)
		XML_SERIALIZE_ELEMENT_TVAR(qint8, val.m_chVal)
		XML_SERIALIZE_ELEMENT_TVAR(quint8, val.m_uchval)
		XML_SERIALIZE_ELEMENT_TVAR(qint16, val.m_sVal)
		XML_SERIALIZE_ELEMENT_TVAR(quint16, val.m_usVal)
		XML_SERIALIZE_ELEMENT_TVAR(qint32, val.m_nIntVal)
		XML_SERIALIZE_ELEMENT_TVAR(quint32, val.m_unIntVal)
		XML_SERIALIZE_ELEMENT_TVAR(qint64, val.m_n64Val)
		XML_SERIALIZE_ELEMENT_TVAR(quint64, val.m_un64Val)

		XML_SERIALIZE_ELEMENT_TVAR(qreal,	val.m_doubleVal)
		XML_SERIALIZE_ELEMENT_TVAR(float,	val.m_floatVal)
		XML_SERIALIZE_ELEMENT_TVAR(bool,	val.m_bVal)

		XML_SERIALIZE_ELEMENT_TVAR(string,	val.m_strEnglish)
		XML_SERIALIZE_ELEMENT_TVAR(中文 ,	val.m_strChinese)
	END_XML_SERIALIZE()
#else
	BEGIN_XML_SERIALIZE(XML_Element_Object)
		XML_SERIALIZE_ELEMENT_TVAR(int8, val.m_chVal)
		XML_SERIALIZE_ELEMENT_TVAR(uint8, val.m_uchval)
		XML_SERIALIZE_ELEMENT_TVAR(int16, val.m_sVal)
		XML_SERIALIZE_ELEMENT_TVAR(uint16, val.m_usVal)
		XML_SERIALIZE_ELEMENT_TVAR(int32, val.m_nIntVal)
		XML_SERIALIZE_ELEMENT_TVAR(uint32, val.m_unIntVal)
		XML_SERIALIZE_ELEMENT_TVAR(int64, val.m_n64Val)
		XML_SERIALIZE_ELEMENT_TVAR(uint64, val.m_un64Val)

		XML_SERIALIZE_ELEMENT_TVAR(double,	val.m_doubleVal)
		XML_SERIALIZE_ELEMENT_TVAR(float,	val.m_floatVal)
		XML_SERIALIZE_ELEMENT_TVAR(bool,	val.m_bVal)

		XML_SERIALIZE_ELEMENT_TVAR(string,	val.m_strEnglish)
		XML_SERIALIZE_ELEMENT_TVAR(中文 ,	val.m_strChinese)
	END_XML_SERIALIZE()
#endif
}
