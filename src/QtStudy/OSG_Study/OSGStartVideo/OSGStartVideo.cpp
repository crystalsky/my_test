#include "OSGStartVideo.h"

namespace OSG_Video{
	OSGStartVideo::OSGStartVideo(QWidget* pParnet)
		: CFunctionOSGViewerWidget("OSGStartVideo", pParnet) 
	{
		QStringList listFunctional = QStringList()
			<< "T03_OSGViewerBase"
			;

		for (int i = 0; i < listFunctional.size(); ++i)
		{
			addFunctional(listFunctional[i]);
		}
	}

	OSGStartVideo::~OSGStartVideo()
	{

	}

	void OSGStartVideo::slotButtonClicked( const QString& strFunctionButtonName )
	{
		CFunctionOSGViewerWidget::slotButtonClicked(strFunctionButtonName);
	}

}
