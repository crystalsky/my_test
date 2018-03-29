#ifndef OSGStartVideo_h__
#define OSGStartVideo_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "CFunctionOSGViewerWidget.h"
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

namespace OSG_Video
{
	class OSGStartVideo : public CFunctionOSGViewerWidget
	{
	public:
		OSGStartVideo(QWidget* pParnet = NULL);
		~OSGStartVideo();

	protected:
		void slotButtonClicked(const QString& strFunctionButtonName);


	protected:

	private:
	};
}

#endif // OSGStartVideo_h__
