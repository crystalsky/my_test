#include "T03.h"
#include "T03/T03_P050_PositionAttitudeTransform.h"
#include "T03/T03_P051_MatrixTransform.h"
#include "T03/T03_P054_AutoTransform.h"
#include "T03/T03_P057_Switch.h"
#include "T03/T03_P059_LOD.h"
#include "T03/T03_P061_PagedLOD.h"
#include "T03/T03_P064_Imposter.h"

namespace OSG_ProgramingGuid{

T03::T03(QWidget* pParnet)
	: CFunctionOSGViewerWidget("OSG_ProgramingGuid-T03", pParnet) 
{
#ifndef USE_REFLECT_OBJECT
	m_mapOSGFuncBase["T03_P051_MatrixTransform"] = 
		CreateMapOSGFuncBase<T03_P051_MatrixTransform>()();
	m_mapOSGFuncBase["T03_P054_AutoTransform"] = 
		CreateMapOSGFuncBase<T03_P054_AutoTransform>()();
	m_mapOSGFuncBase["T03_P057_Switch"] = 
		CreateMapOSGFuncBase<T03_P057_Switch>()();
	m_mapOSGFuncBase["T03_P059_LOD"] = 
		CreateMapOSGFuncBase<T03_P059_LOD>()();
	m_mapOSGFuncBase["T03_P061_PagedLOD"] = 
		CreateMapOSGFuncBase<T03_P061_PagedLOD>()();
	m_mapOSGFuncBase["T03_P064_Imposter"] = 
		CreateMapOSGFuncBase<T03_P064_Imposter>()();

	QMapIterator<QString, QSharedPointer<MyOSGFuncBase>> iter(m_mapOSGFuncBase);
	while (iter.hasNext())
	{
		QString strKey = iter.next().key();
		strKey.remove("T03_");
		addFunctional(strKey);
	}
#else
	QStringList listFunctional = QStringList()
		<< "P050_PositionAttitudeTransform"
		<< "P051_MatrixTransform"
		<< "P054_AutoTransform"
		<< "P057_Switch"
		<< "P059_LOD"
		<< "P061_PagedLOD"
		<< "P064_Imposter"
		<< "P067_OccluderNode"
		<< "P071_CoordinateSystemNode"
		<< "P074_CopyOp1"
		<< "P079_CopyOp2";
	for (int i = 0; i < listFunctional.size(); ++i)
	{
		addFunctional(listFunctional[i]);
	}
#endif
}

T03::~T03()
{
	
}

void T03::slotButtonClicked( const QString& strFunctionButtonName )
{
#ifndef USE_REFLECT_OBJECT

	QSharedPointer<MyOSGFuncBase> pFuncBase = 
		m_mapOSGFuncBase.value(strFunctionButtonName);
	if (!pFuncBase.isNull())
	{
		m_pViewerWidget->setSceneData(pFuncBase->getNode());
	}
	else
	{

	}
#else
	CFunctionOSGViewerWidget::slotButtonClicked(strFunctionButtonName);
#endif
}

}