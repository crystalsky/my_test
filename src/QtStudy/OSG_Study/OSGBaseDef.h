#ifndef OSGBaseDef_h__
#define OSGBaseDef_h__

#include <QSharedPointer>
#include <QMap>
#include <assert.h>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include "ReflectObject.h"

namespace osg
{
	class Node;
}

class ViewerWidget;
class OSGFuncBase : public UtilityKit::CReflectedObject
{
public:
	OSGFuncBase();
	virtual ~OSGFuncBase(){}
	virtual osg::Node* getNode(){return NULL;}

	inline bool hasOwnerViewerWidget()const{return m_bhasOwnerViewerWidget;}
	virtual ViewerWidget* getViewerWidget();

	virtual void init(){}
protected:
	bool _initOwnViewerWidget(bool hasOwnViewerWidget = false);
protected:
	bool m_bInit;
private:
	bool m_bhasOwnerViewerWidget;
	static QMap<OSGFuncBase*, ViewerWidget*>	m_mapOSGFuncViewerWidget;
};
typedef OSGFuncBase ReflectedOSGFuncBase;


typedef osg::Node* (OSGFuncBase::*Get_Node)(); 

class MyOSGFuncBase
{
public:
	MyOSGFuncBase(OSGFuncBase* pBase, Get_Node pFunc)
		: m_pOSGFuncBase(NULL)
	{
		assert(pBase != NULL && pFunc != NULL);
		m_pOSGFuncBase = pBase;
		m_pFuncGetNode = pFunc;
	}

	~MyOSGFuncBase()
	{
		if (m_pOSGFuncBase != NULL)
		{
			delete m_pOSGFuncBase;
			m_pOSGFuncBase = NULL;
		}
	}

	osg::Node* getNode()
	{
		if (m_pFuncGetNode && m_pOSGFuncBase)
		{
			return (m_pOSGFuncBase->*m_pFuncGetNode)();
		}
		return NULL;
	}
private:
	Get_Node		m_pFuncGetNode;
	OSGFuncBase*	m_pOSGFuncBase;
};

typedef QMap<QString, QSharedPointer<MyOSGFuncBase>> MapOSGFuncBase;

template<typename T_Base>
struct CreateMapOSGFuncBase
{
	QSharedPointer<MyOSGFuncBase> operator()()
	{
		QSharedPointer<MyOSGFuncBase> ptrOSGFuncBase(
			new MyOSGFuncBase(new T_Base(), (Get_Node)&T_Base::getNode));

		return ptrOSGFuncBase;
	}
};

namespace Kit
{
	template <typename T_OSGFuncBase>
	class MyOSGFuncBase
	{
	public:
		MyOSGFuncBase()
			: m_pOSGFuncBase(NULL)
		{
			m_pOSGFuncBase = new T_OSGFuncBase();
			m_pFuncGetNode = (Get_Node)&T_OSGFuncBase::getNode;
		}

		~MyOSGFuncBase()
		{
			if (m_pOSGFuncBase != NULL)
			{
				delete m_pOSGFuncBase;
				m_pOSGFuncBase = NULL;
			}
		}

		osg::Node* getNode()
		{
			if (m_pFuncGetNode && m_pOSGFuncBase)
			{
				return (m_pOSGFuncBase->*m_pFuncGetNode)();
			}
			return NULL;
		}
	private:
		Get_Node		m_pFuncGetNode;
		T_OSGFuncBase*	m_pOSGFuncBase;
	};

	typedef QMap<QString, MyOSGFuncBase<OSGFuncBase>*> MapOSGFuncBase;
}




#endif // OSGBaseDef_h__
