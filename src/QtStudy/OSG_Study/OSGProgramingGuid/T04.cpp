#include "T04.h"

namespace OSG_ProgramingGuid{
T04::T04(QWidget* pParnet)
	: CFunctionOSGViewerWidget("OSG_ProgramingGuid-T04", pParnet) 
{
	QStringList listFunctional = QStringList()
		<< "P88_Geometry_Basic"
		<< "P90_Geometry_Index"
		<< "P88_Geometry_Basic"
		<< "P95_ShapeDrawable"
		<< "P98_Tessellator"
		<< "P102_Simplifier"
		<< "P105_Delaunay"
		<< "P108_TriStripVisitor"
		<< "P112_SmoothingVisitor"
		;

	for (int i = 0; i < listFunctional.size(); ++i)
	{
		addFunctional(listFunctional[i]);
	}
}

T04::~T04()
{
	
}

void T04::slotButtonClicked( const QString& strFunctionButtonName )
{
	CFunctionOSGViewerWidget::slotButtonClicked(strFunctionButtonName);
}

}