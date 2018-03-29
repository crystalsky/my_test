#ifndef _H__XML_RELECTED_OBJECT_H_
#define _H__XML_RELECTED_OBJECT_H_

#include "_XML_Container_Object.h"

class XML_RelectObject : public XmlSerialize::XmlSerializeRefletObject
{
	DECLARE_REFLECTED_CLASS(XML_RelectObject)
private:
	XML_Container_Object m_obj;

public:
	XML_RelectObject(int nArraySize = 1)
		: m_obj(nArraySize){}

	bool operator == (const XML_RelectObject& ref)const
	{
		return m_obj == ref.m_obj;
	}
	virtual tinyxml2::XMLElement* XmlSerialize(XmlSerialize::XmlSerializerBase* pXmlSerializer,tinyxml2::XMLElement* pParentElement = NULL,const char* szLocalElementName = NULL)
	{
		BEGIN_XML_SERIALIZE(XML_RelectObject)
			XML_SERIALIZE_OBJECT_TVAR(m_obj);
		END_XML_SERIALIZE()
	}
};

static bool equal1(const XML_RelectObject* p1, const XML_RelectObject* p2)
{
	return *p1 == *p2;
}

struct equal2 : public std::binary_function<XML_RelectObject*, XML_RelectObject*, bool>
{
	bool operator()(const XML_RelectObject* p1, const XML_RelectObject* p2)const
	{
		return *p1 == *p2;
	}
};

class CGroupReflectedContainerObject : public XmlSerialize::XmlSerializeObject
{
public:
    CGroupReflectedContainerObject(int nSize = 1)
	{
#ifdef XMLSERIALIZE_QT_SUPPORT
		xml_data_gen_functions::GenData<XML_RelectObject*, QVector<XML_RelectObject*>>::
			gendata(m_vecDataItemsPtr, nSize);
		xml_data_gen_functions::GenData<XML_RelectObject*, QList<XML_RelectObject*>>::
			gendata(m_listItemsPtr, nSize);
#else
		xml_data_gen_functions::GenData<XML_RelectObject*, std::vector<XML_RelectObject*>>::
			gendata(m_vecDataItemsPtr, nSize);
		xml_data_gen_functions::GenData<XML_RelectObject*, std::list<XML_RelectObject*>>::
			gendata(m_listItemsPtr, nSize);
#endif
	}
    ~CGroupReflectedContainerObject(){}

    CGroupReflectedContainerObject &operator=(CGroupReflectedContainerObject &rhs);

	bool operator == (const CGroupReflectedContainerObject& ot)const
	{
		return std::equal(this->m_vecDataItemsPtr.begin(), this->m_vecDataItemsPtr.end(), 
			ot.m_vecDataItemsPtr.begin(), equal1) &&
			std::equal(this->m_listItemsPtr.begin(), this->m_listItemsPtr.end(), 
			ot.m_listItemsPtr.begin(), equal2());
	}
public:
#ifdef XMLSERIALIZE_QT_SUPPORT
	QVector<XML_RelectObject*> m_vecDataItemsPtr;
	QList<XML_RelectObject*> m_listItemsPtr;
#else
	std::vector<XML_RelectObject*> m_vecDataItemsPtr;
	std::list<XML_RelectObject*> m_listItemsPtr;
#endif
public:
	virtual tinyxml2::XMLElement* XmlSerialize(XmlSerialize::XmlSerializerBase* pXmlSerializer,tinyxml2::XMLElement* pParentElement = NULL,const char* szLocalElementName = NULL)
	{
		BEGIN_XML_SERIALIZE(CGroupReflectedContainerObject)
			//OK
			XML_SERIALIZE_REFLECT_CONTAINER_OBJECT(VectorXMLItemsPtr, XML_RelectObject, Type, <>, m_vecDataItemsPtr)
			//OK
			XML_SERIALIZE_REFLECT_CONTAINER_OBJECT(ListXMLItemsPtr, XML_RelectObject, Type, <>, m_listItemsPtr)
		END_XML_SERIALIZE()
	}

public:
};
#endif //_H__XML_RELECTED_OBJECT_H_
