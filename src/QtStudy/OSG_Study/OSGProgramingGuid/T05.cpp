#include "T05.h"

namespace OSG_ProgramingGuid{
T05::T05(QWidget* pParnet)
	: CFunctionOSGViewerWidget("OSG_ProgramingGuid-T05", pParnet) 
{
	QStringList listFunctional = QStringList()
		<< "P119_ClipNode"
		;

	for (int i = 0; i < listFunctional.size(); ++i)
	{
		addFunctional(listFunctional[i]);
	}
}

T05::~T05()
{
	
}

}
