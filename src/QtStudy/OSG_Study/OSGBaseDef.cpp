#include "OSGBaseDef.h"
#include "osgviewerQt.h"

QMap<OSGFuncBase*, ViewerWidget*> OSGFuncBase::m_mapOSGFuncViewerWidget = QMap<OSGFuncBase*, ViewerWidget*>();

OSGFuncBase::OSGFuncBase()
	: m_bhasOwnerViewerWidget(false)
	, m_bInit(false)
{
	
}

ViewerWidget* OSGFuncBase::getViewerWidget()
{
	return m_mapOSGFuncViewerWidget.value(this);
}

bool OSGFuncBase::_initOwnViewerWidget( bool hasOwnViewerWidget /*= false*/ )
{
	m_bhasOwnerViewerWidget = hasOwnViewerWidget;

	if (m_bhasOwnerViewerWidget)
	{
		if (!m_mapOSGFuncViewerWidget.contains(this))
		{
			ViewerWidget* pWidget = new ViewerWidget();
			m_mapOSGFuncViewerWidget[this] = pWidget;
		}
	}

	return true;
}
