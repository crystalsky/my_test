#ifndef T03_h__
#define T03_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "CFunctionOSGViewerWidget.h"

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <osgGA/GUIEventHandler>
#include <osg/AutoTransform>
#include "OSGBaseDef.h"
#include "ReflectObject.h"

namespace OSG_ProgramingGuid
{
#define  USE_REFLECT_OBJECT
	class T03 : public CFunctionOSGViewerWidget
	{
	public:
		T03(QWidget* pParnet = NULL);
		~T03();

	public:

	protected:
		void slotButtonClicked(const QString& strFunctionButtonName);

	private:
		template<class T>
		bool _createOSGFuncBase();
	private:

#ifndef USE_REFLECT_OBJECT
		MapOSGFuncBase m_mapOSGFuncBase;
#endif

		Kit::MapOSGFuncBase m_mapOSGFuncBaseEx;


	};

}

#endif // T03_h__
