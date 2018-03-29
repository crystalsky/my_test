#ifndef _H__XML_CONTAINER_ELEMENT_OBJECT_H_
#define _H__XML_CONTAINER_ELEMENT_OBJECT_H_

#include "xml_data_gen_functions.h"

struct XML_Container_Element_Object : public XmlSerialize::XmlSerializeObject
{
	XML_Container_Element_Object(int nSize = 1);

	bool operator == (const XML_Container_Element_Object& other)const
	{
		return m_lstString == other.m_lstString &&
			m_vecString == other.m_vecString &&
			m_vecIntValues == other.m_vecIntValues &&
			m_lstIntValues == other.m_lstIntValues &&
			m_vecIntValues == other.m_vecIntValues &&
			m_lstIntValues == other.m_lstIntValues;
	}
#ifdef XMLSERIALIZE_QT_SUPPORT
	QList<QString>		m_lstString;
	QVector<QString>	m_vecString;

	QVector<int>		m_vecIntValues;
	QList<int>			m_lstIntValues;

	QVector<double>	m_vecDoubleValues;
	QList<double>	m_lstDoubleValues;
#else
	std::list<std::string> m_lstString;
	std::list<std::string> m_vecString;

	std::vector<int>	m_vecIntValues;
	std::list<int>	m_lstIntValues;

	std::vector<double>	m_vecDoubleValues;
	std::list<double>	m_lstDoubleValues;
#endif

public:
	virtual CXmlElement* XmlSerialize(XmlSerialize::XmlSerializerBase* pXmlSerializer,CXmlElement* pParentElement = NULL,
		const char* szLocalElementName = NULL);
};

#endif //_H__XML_CONTAINER_ELEMENT_OBJECT_H_