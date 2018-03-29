#ifndef _H__XML_CONTAINER_OBJECT_H_
#define _H__XML_CONTAINER_OBJECT_H_

#include "_XML_Herited_Object.h"
#include "_XML_Container_Element_Object.h"
#include <memory>

#ifdef XMLSERIALIZE_QT_SUPPORT
#pragma message("-->message: Use The XMLSERIALIZE_QT_SUPPORT")
typedef QVector<XML_Container_Element_Object> VectorContainer;
typedef QList<XML_Container_Element_Object> ListContainer;

typedef QVector<XML_Container_Element_Object*> VectorContainerPtr;
typedef QList<XML_Container_Element_Object*> ListContainerPtr;
#else
typedef std::vector<XML_Container_Element_Object> VectorContainer;
typedef std::list<XML_Container_Element_Object> ListContainer;

typedef std::vector<XML_Container_Element_Object*> VectorContainerPtr;
typedef std::list<XML_Container_Element_Object*> ListContainerPtr;
#endif

#ifdef XMLSERIALIZE_SHARED_PTR_SUPPORT
	#ifdef XMLSERIALIZE_QT_SUPPORT
		template<class T>
		class SharedPtr : public QSharedPointer<T>
		{
		public:
			SharedPtr(T *ptr) : QSharedPointer<T>(ptr){}
		};
		typedef QVector<QSharedPointer<XML_Container_Element_Object>> VectorSharedPtrContainer;
		typedef QList<QSharedPointer<XML_Container_Element_Object>> ListSharedPtrContainer;
	#else
		#if defined(XMLSERIALIZE_BOOST_SUPPORT)
			template<class T>
			class SharedPtr : public boost::shared_ptr<T>
			{
			public:
				SharedPtr(T *ptr) : boost::shared_ptr<T>(ptr){}
			};
			typedef std::vector<boost::shared_ptr<XML_Container_Element_Object>> VectorSharedPtrContainer;
			typedef std::list<boost::shared_ptr<XML_Container_Element_Object>> ListSharedPtrContainer;
		#else

			#ifdef __cplusplus >= 201103L //for c++11
				template<class T>
				class SharedPtr : public std::shared_ptr<T>
				{
				public:
					SharedPtr(T *ptr) : std::shared_ptr<T>(ptr){}
				};
				typedef std::vector<SharedPtr<XML_Container_Element_Object>>  VectorSharedPtrContainer;
				typedef std::list<SharedPtr<XML_Container_Element_Object>>  ListSharedPtrContainer;
			#else
				typedef std::vector<std::auto_ptr<XML_Container_Element_Object>>  VectorSharedPtrContainer;
				typedef std::list<std::auto_ptr<XML_Container_Element_Object>>  ListSharedPtrContainer;
			#endif	
		#endif
	#endif
#endif


struct XML_Container_Object : public XmlSerialize::XmlSerializeObject
{
	XML_Container_Object(int nSize = 1, bool flowSize = false);
	~XML_Container_Object();

	VectorContainer m_vecXmlObject;
	ListContainer m_listXMLObject;

	VectorContainerPtr m_vecXmlObjectPtr;
	VectorContainerPtr m_listXMLObjectPtr;

#ifdef XMLSERIALIZE_SHARED_PTR_SUPPORT
	VectorSharedPtrContainer m_vecXmlObjectSharedPtr;
	ListSharedPtrContainer m_listXMLObjectSharedPtr;
#endif
	
public:
	bool operator == (const XML_Container_Object& oter)const
	{
		bool equal = m_vecXmlObject == oter.m_vecXmlObject &&
			m_listXMLObject == oter.m_listXMLObject;

		return equal;
	}
public:
	virtual CXmlElement* XmlSerialize(XmlSerialize::XmlSerializerBase* pXmlSerializer, CXmlElement* pParentElement = NULL,
		const char* szLocalElementName = NULL);
};


#endif //_H__XML_CONTAINER_OBJECT_H_
