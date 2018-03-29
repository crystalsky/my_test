#include "EMDataShow.h"
#include <iostream>
//#include "VRMainFrame/editordata.h"
//#include "VRMainFrame/mainwindow.h"
//#include "VRMainFrame/pluginmanager.h"
//#include "VRMainFrame/editorevents.h"
//#include "dtUtil\log.h"
//#include "QU_DebugString.h"
//#include "QU_String.h"
#include <QFile>
#include <QDir>
#include "ColorMgr.h"
#include "Lagrange2.h"
//#include "VRMainFrame\ConfigDataAndEvent.h"
#include "osg\PolygonOffset"
#include "EMDataCaching.h"
//#include "Earth3DPlugin\EarthData.h"
//#include "Earth2DPlugin\EarthData2D.h"

CEMDataShow::CEMDataShow( QObject* pParent /*= NULL*/ )
	: m_b3DSinglePicture(true)
	//, m_heiLayersGroup3D(new osg::Group)
	//, m_heiLayersGroup2D(new osg::Group)
	, m_bInit(false)
	//, m_mainWindow(VRMainFrame::EditorData::GetInstance().getMainWindow())
	, m_pEMDataCaching(new CEMDataCaching(this))
{
	//connect(&(VRMainFrame::EditorEvents::GetInstance()), SIGNAL(currentMapChanged()), SLOT(slotNewMapOpen()));
	connect(m_pEMDataCaching, SIGNAL(singalEMDataReaded(const QString&)), SLOT(slotEMDataReaded(const QString&)));

	//m_heiLayersGroup3D->setDataVariance(osg::Object::DYNAMIC);
	//m_heiLayersGroup3D->getOrCreateStateSet()->setMode(GL_LIGHTING,0);

	//m_heiLayersGroup2D->setDataVariance(osg::Object::DYNAMIC);
	//m_heiLayersGroup2D->getOrCreateStateSet()->setMode(GL_LIGHTING,0);
	//m_heiLayersGroup2D->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,0);
}

CEMDataShow::~CEMDataShow()
{

}

void CEMDataShow::slotNewMapOpen()
{
	if (!m_bInit)
	{
		//EarthData::getInstance()->getEarthRoot()->addChild(m_heiLayersGroup3D.get());
		//EarthData2D::getInstance()->getEarthRoot()->addChild(m_heiLayersGroup2D.get());

		m_bInit = true;
	}
}

bool CEMDataShow::setListEMData( const EMShowDef::ListEMDataFileInfo& listFileInfo )
{
	if (!m_pEMDataCaching)
	{
		return false;
	}

	m_pEMDataCaching->setListEMData(listFileInfo);

	return true;
}

bool CEMDataShow::showEMFileData(const EMShowDef::EMDataFileInfo& info, bool b3D)
{
	if (!m_pEMDataCaching)
	{
		return false;
	}

	const QString& strID = info.getID();
	if (m_pEMDataCaching->existEMData(strID))
	{
		QSharedPointer<EMShowDef::EMDataInfo> data;

		m_pEMDataCaching->getEMData(info.getID(), data);

		_showEMData(data, b3D);

		return true;
	}
	else
	{
		m_pEMDataCaching->setEMData(info);
		
		if (b3D)
		{
			m_bWaitingShow3D = true;
			m_strCurDisplayedEMDataID_3D = strID;
		}
		else
		{
			m_bWaitingShow2D = true;
			m_strCurDisplayedEMDataID_2D = strID;
		}
	}
	return false;
}


bool CEMDataShow::_showEMData(const QSharedPointer<EMShowDef::EMDataInfo>& data, bool b3D /*= true*/ )
{
	if (data.isNull()||!data->valid())
	{
		return false;
	}

	if (b3D)
	{
		/*osg::ref_ptr<osg::Geometry> quadsGeom = new osg::Geometry;
		
		osg::Geode* quadsGeo3D = new osg::Geode;

		quadsGeo3D->setName(data->_fileInfo.getID().toLocal8Bit().data());
		quadsGeom->setVertexArray(data->_arrVertex3D.get());
		quadsGeom->setColorArray(data->_arrColor.get(), osg::Array::BIND_PER_VERTEX);
		quadsGeom->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		quadsGeom->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );		
		quadsGeom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,data->_arrVertex3D->size()));
		quadsGeo3D->addDrawable(quadsGeom.get());
		osg::PolygonOffset* textOffset=new osg::PolygonOffset;
		textOffset->setFactor(-10.0f - m_heiLayersGroup3D->getNumChildren());
		textOffset->setUnits(10.0f);
		quadsGeom->getOrCreateStateSet()->setAttributeAndModes(textOffset);

		if (m_b3DSinglePicture)
		{
			_clear3D();
		}
		else
		{
			//TODO:
		}
		m_heiLayersGroup3D->addChild(quadsGeo3D);*/
	}
	else
	{/*
		///< start 2D
		osg::ref_ptr<osg::Geometry> quadsGeom2D = new osg::Geometry;
		osg::Geode* quadsGeo2D = new osg::Geode;
		quadsGeo2D->setName(data->_fileInfo.getID().toLocal8Bit().data());

		quadsGeom2D->setVertexArray(data->_arrVertex2D.get());
		quadsGeom2D->setColorArray(data->_arrColor.get(),osg::Array::BIND_PER_VERTEX);
		quadsGeom2D->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		quadsGeom2D->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );		
		quadsGeom2D->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,data->_arrVertex2D->size()));
		quadsGeo2D->addDrawable(quadsGeom2D.get());	
		quadsGeo2D->getOrCreateStateSet()->setRenderBinDetails(99 + m_heiLayersGroup3D->getNumChildren(), "RenderBin");	

		for (int i = 0; i < m_heiLayersGroup2D->getNumChildren(); ++i)
		{
			m_heiLayersGroup2D->removeChild(i);
		}
		m_heiLayersGroup2D->addChild(quadsGeo2D);*/
	}
	return true;
}

void CEMDataShow::_removeChildFromLayersGroup( const std::string& idStr , bool is3D)
{/*
	if (is3D)
	{
		for (int i = 0; i < m_heiLayersGroup3D->getNumChildren(); ++i)
		{
			if (m_heiLayersGroup3D->getChild(i)->getName() == idStr)
			{
				m_heiLayersGroup3D->removeChild(i);
			}
		}
	}
	else
	{
		for (int i = 0; i < m_heiLayersGroup2D->getNumChildren(); ++i)
		{
			if (m_heiLayersGroup2D->getChild(i)->getName() == idStr)
			{
				m_heiLayersGroup2D->removeChild(i);
			}
		}
	}*/
}

bool CEMDataShow::removeEMShow( const EMShowDef::EMDataFileInfo& info, bool b3D )
{
	if (info.valid())
	{
		_removeChildFromLayersGroup(info.getID().toLocal8Bit().data(), b3D);

		return true;
	}
	return false;
}

void CEMDataShow::_clear3D()
{
	//m_heiLayersGroup3D->removeChildren(0, m_heiLayersGroup3D->getNumChildren());
}

void CEMDataShow::_clear2D()
{
	//m_heiLayersGroup2D->removeChildren(0, m_heiLayersGroup2D->getNumChildren());
}

bool CEMDataShow::reset()
{
	_clear3D();

	_clear2D();

	if (m_pEMDataCaching)
	{
		m_pEMDataCaching->reset();
	}

	return true;
}

void CEMDataShow::setShowState( bool val )
{
	if (val == m_bShowState)
	{
		return;
	}

	m_bShowState = val;

	//m_heiLayersGroup3D->setNodeMask(val ? 1 : 0);
	//m_heiLayersGroup2D->setNodeMask(val ? 1 : 0);
}

void CEMDataShow::set3DSinglePicture( bool val )
{
	m_b3DSinglePicture = val;
}

void CEMDataShow::slotEMDataReaded( const QString& strID )
{
	if (m_bWaitingShow3D || m_bWaitingShow2D)
	{
		QSharedPointer<EMShowDef::EMDataInfo> data;
		m_pEMDataCaching->getEMData(strID, data);

		if (m_strCurDisplayedEMDataID_3D == strID && m_bWaitingShow3D)
		{
			_showEMData(data, true);

			m_bWaitingShow3D = false;
		}

		if (m_strCurDisplayedEMDataID_2D.contains(strID) && m_bWaitingShow2D)
		{
			_showEMData(data, false);
			m_bWaitingShow2D = false;
		}
	}
	
}

void CEMDataShow::setThresholdValue( double val )
{
	if (!m_pEMDataCaching)
	{
		return;
	}

	m_pEMDataCaching->setThresholdValue(val);
}

void CEMDataShow::setShowHeightScale( int val )
{
	if (!m_pEMDataCaching)
	{
		return;
	}

	m_pEMDataCaching->setShowHeightScale(val);
}

void CEMDataShow::setAlphaVal( double val )
{
	if (!m_pEMDataCaching)
	{
		return;
	}
	m_pEMDataCaching->setAlphaVal(val);
}

void CEMDataShow::clearNodes()
{
	_clear3D();
	_clear2D();
}
