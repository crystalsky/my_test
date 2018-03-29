#include "EMDataCaching.h"
#include <iostream>
#include "dtUtil\log.h"
#include "QU_DebugString.h"
#include "QU_String.h"
#include <QFile>
#include <QDir>
#include "ColorMgr.h"
#include "Lagrange2.h"
#include <QtConcurrent/QtConcurrent>

CEMDataCaching::CEMDataCaching( QObject* pParent /*= NULL*/ )
	: QThread(pParent)
	, m_nMaxCacheSize(100)
	, m_dMaxValue(INVALIDE_MIN_VALUE)
	, m_dMinValue(INVALIDE_MAX_VALUE)
	, m_nShowHeightScale(10000)
	, m_dThresholdValue(-120)
	, m_dalphaVal(0.5)
	, m_bRunning(true)
{
	connect(&m_watcher, SIGNAL(finished()), SLOT(slotFinished()));
	connect(&m_watcher, SIGNAL(resultReadyAt(int)), 
		SLOT(slotResultReadyAt(int)));

	start();
}

CEMDataCaching::~CEMDataCaching()
{
	m_bRunning = false;

	if (m_watcher.isRunning())
	{
		m_watcher.cancel();
	}
	wait(500);
}

void CEMDataCaching::slotFinished()
{
	m_TempList.clear();
}

bool CEMDataCaching::setListEMData( const EMShowDef::ListEMDataFileInfo& listFileInfo )
{
	if (listFileInfo.isEmpty())
	{
		return false;
	}
	
	{
		QMutexLocker loker(&m_mutexMapCachedEMData);
		m_mapCachedData.clear();
	}

	QMutexLocker locker(&m_mutex);
	for (int i = 0; i < listFileInfo.size(); i++)
	{
		EMShowDef::EMDataFileInfo info = listFileInfo[i];
		_setEMData(info, false);
	}

	return true;
}

bool CEMDataCaching::setEMData( const EMShowDef::EMDataFileInfo& fileInfo )
{
	_setEMData(fileInfo);

	return true;
}


bool CEMDataCaching::_setEMData( const EMShowDef::EMDataFileInfo& fileInfo, bool bLock /*= true*/ )
{
	if (existEMData(fileInfo.getID()) || m_TempList.contains(fileInfo))
	{
		return false;
	}

	EMShowDef::EMDataFileInfo& info = const_cast<EMShowDef::EMDataFileInfo&>(fileInfo);
	info._userData = this;

	if (bLock)
	{
		QMutexLocker locker(&m_mutex);
		m_listFileInfo << fileInfo;
		m_TempList << fileInfo;
	}
	else
	{
		m_listFileInfo << fileInfo;
		m_TempList << fileInfo;
	}

	return true;
}

bool CEMDataCaching::reset()
{
	QMutexLocker locker(&m_mutexMapCachedEMData);
	m_mapCachedData.clear();

	QMutexLocker locker1(&m_mutexMaxMin);
	m_dMinValue = INVALIDE_MAX_VALUE;
	m_dMaxValue = INVALIDE_MIN_VALUE;

	return true;
}

bool CEMDataCaching::existEMData( const QString& strID )
{
	QMutexLocker locker(&m_mutexMapCachedEMData);
	return m_mapCachedData.contains(strID);
}

bool CEMDataCaching::getEMData( const QString& strID, QSharedPointer<EMShowDef::EMDataInfo>& destData )
{
	QMutexLocker locker(&m_mutexMapCachedEMData);
	if (m_mapCachedData.contains(strID))
	{
		destData = m_mapCachedData.value(strID);
		return true;
	}

	return false;
}

bool CEMDataCaching::removeEMData( const QString& strID )
{
	QMutexLocker locker(&m_mutexMapCachedEMData);
	if (m_mapCachedData.contains(strID))
	{
		m_mapCachedData.remove(strID);
		return true;
	}
	return false;
}

void CEMDataCaching::run()
{
	while (m_bRunning)
	{
		{
			QMutexLocker locker(&m_mutex);
			if (m_listFileInfo.isEmpty())
			{
				msleep(50);
				continue;
			}
		}

		{
			QMutexLocker locker(&m_mutex);
			EMShowDef::ListEMDataFileInfo templist = m_listFileInfo;
			m_listFileInfo.clear();
			locker.unlock();

			m_watcher.setFuture(QtConcurrent::mapped(templist, convertData));
			m_watcher.waitForFinished();
		}
	}

	qDebug()<<"CEMDataCaching Threading Exit!......";
}

void CEMDataCaching::slotResultReadyAt( int nIndex )
{
	{
		QMutexLocker loker(&m_mutexMapCachedEMData);

		if (m_mapCachedData.size() > m_nMaxCacheSize)
		{
			m_mapCachedData.erase(m_mapCachedData.begin());
		}
	}

#ifdef USE_SHARED_PTR
	QSharedPointer<EMShowDef::EMDataInfo> info = m_watcher.resultAt(nIndex);
	if (!info.isNull() && info->valid())
	{
		m_mapCachedData.insert(info->_fileInfo.getID(), info);
		emit singalEMDataReaded(info->_fileInfo.getID());
	}
#else
	EMShowDef::EMDataInfo* info = m_watcher.resultAt(nIndex);
	delete info;
	info = NULL;
	qDebug()<< "2222222222222222";
	if (info != NULL && info->valid())
	{
		m_mapCachedData.insert(info->_fileInfo.getID(), QSharedPointer<EMShowDef::EMDataInfo>(info));
		emit singalEMDataReaded(info->_fileInfo.getID());
	}
#endif
}

#ifdef USE_SHARED_PTR
QSharedPointer<EMShowDef::EMDataInfo> CEMDataCaching::convertData( const EMShowDef::EMDataFileInfo& srcData )
{
	QSharedPointer<EMShowDef::EMDataInfo> retData;

	CEMDataCaching* pThis = reinterpret_cast<CEMDataCaching*>(srcData._userData);

	if (pThis != NULL)
	{
		retData = QSharedPointer<EMShowDef::EMDataInfo>(pThis->_convertData(srcData));
	}

	return retData;
}

#else

EMShowDef::EMDataInfo* CEMDataCaching::convertData( const EMShowDef::EMDataFileInfo& srcData )
{
	CEMDataCaching* pThis = reinterpret_cast<CEMDataCaching*>(srcData._userData);

	if (pThis)
	{
		return pThis->_convertData(srcData);
	}

	return NULL;
}

#endif

EMShowDef::EMDataInfo* CEMDataCaching::_convertData( const EMShowDef::EMDataFileInfo& srcData )
{
	qDebug()<< "11111111111111111111";
	EMShowDef::EMDataInfo* retData = new EMShowDef::EMDataInfo;
	retData->_fileInfo = srcData;

	EMShowDef::coverageResultData data;

	QTime t;
	t.start();
	if (_readCoverageFile(srcData._strFileFullPath, data))
	{
		retData->_dMinVal = data.m_minValue;
		retData->_dMaxVal = data.m_maxValue;

		_updateMaxMinValue(data.m_maxValue, data.m_minValue);

		//高度放大
		data.m_heigh *= m_nShowHeightScale;

		_convertCoverLayerData(data, *retData);

		static int nTotalTime = 0;
		static int nEverTime = 0;
		static int nCalcTime = 0;
		
		nTotalTime += t.elapsed();
		nEverTime = nTotalTime / ++nCalcTime;

		qDebug() << QString("Thread[%1] Use Time [%2],EverTime=[%3]")
			.arg((int)QThread::currentThreadId()) 
			.arg(t.elapsed())
			.arg(nEverTime);
	}
	else
	{
		qDebug() << QString("===EMDataFile [%1] Read Error")
			.arg(srcData._strFileFullPath);
	}

	return retData;
}

bool CEMDataCaching::_readCoverageFile( const QString& dataFilePath, EMShowDef::coverageResultData& data )
{
	QFile file(dataFilePath);

	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug()<<"coverageResult Open File failed:" + dataFilePath;
		return false;
	}

	int headSize = sizeof(EMShowDef::coverageResultData)  - sizeof(double);
	int fileR = file.read((char*)&data , headSize);

	const int readyReadSize = file.size() - headSize;
	if (readyReadSize % 8 != 0)
	{
		qDebug() << "getCoverageResultData() : readyReadSize % 8 != 0";
		file.close();
		return false;
	}

	const int bufSize = readyReadSize / sizeof(double);
	data.m_data = new  double[bufSize];
	fileR = file.read((char*)data.m_data ,  readyReadSize );
	file.close();
	return true;
}

bool CEMDataCaching::_updateMaxMinValue( double dMax, double dMin )
{
	QMutexLocker locker(&m_mutexMaxMin);
	if (dMax > m_dMaxValue)
	{
		m_dMaxValue = dMax;
	}
	if (dMin < m_dMinValue)
	{
		m_dMinValue = dMin;
	}

	ColorMgr::getInstance()->setMinAndMaxValue(
		m_dMinValue < getThresholdValue() ? getThresholdValue() : m_dMinValue , 
		m_dMaxValue < getThresholdValue() ? getThresholdValue() : m_dMaxValue);

	return true;
}

bool CEMDataCaching::_convertCoverLayerData( const EMShowDef::coverageResultData& data , EMShowDef::EMDataInfo& destData )
{
	if (!data.m_data)
	{
		return false;
	}

	//最后结果对象
	EMShowDef::coverageResultData cvData = data;

	//插值对象
	Lagrange2 objLagrange(data.m_column , data.m_row);

	{
		QVector<double> column;
		QVector<double> row;
		int count = data.m_column > data.m_row ? data.m_column : data.m_row;
		for (int i = 0 ; i < count ; i++)
		{
			column << i;
			row << i;
		}

		QVector<double> dataVec(data.m_column * data.m_row);
		memcpy(dataVec.data() , data.m_data , sizeof(double) * data.m_column * data.m_row);
		objLagrange.input(column , row , dataVec);
	}
	
	//行列插值个数
	const int interpolationScale = 10;

	//计算插件值数据信息
	cvData.m_column = (data.m_column-1) * interpolationScale;
	cvData.m_row = (data.m_row-1) * interpolationScale;
	cvData.m_ratio = data.m_ratio / interpolationScale;
	//cvData.m_heigh = 0;

	//插值后数据大小
	const int newDataCount = cvData.m_column * cvData.m_row;
	
	//释放原来数据并新生成数据
	cvData.release();
	cvData.m_data = new double[newDataCount];
	
	double minValue = INVALIDE_MAX_VALUE , maxValue = INVALIDE_MIN_VALUE;
	double* temValue = cvData.m_data;
	for (double row = 0 ; row < cvData.m_row ; row++)
	{
		for (double column = 0 ; column < cvData.m_column ; column++ , temValue++)
		{
			*temValue = objLagrange.interp(column / interpolationScale , row / interpolationScale);
			if (*temValue <= INVALIDE_MIN_VALUE)
			{
				continue;
			}
			
			if (minValue > *temValue)
			{
				minValue = *temValue;
			}
			
			if (maxValue < *temValue)
			{
				maxValue = *temValue;
			}
		}
	}

	_updateMaxMinValue(maxValue, minValue);

	//
	if (destData._arrVertex3D.valid())
	{
		destData._arrVertex3D->clear();
	}
	else
	{
		destData._arrVertex3D = new osg::Vec3Array();
	}
	destData._arrVertex3D->reserve(4 * newDataCount);
	
	if (destData._arrVertex2D.valid())
	{
		destData._arrVertex2D->clear();
	}
	else
	{
		destData._arrVertex2D = new osg::Vec3Array();
	}
	destData._arrVertex2D->reserve(4 * newDataCount);

	if (destData._arrColor.valid())
	{
		destData._arrColor->clear();
	}
	else
	{
		destData._arrColor = new osg::Vec4Array();
	}
	destData._arrColor->reserve(4 * newDataCount);
	
	//////////////////////////////////////////
	for (int row = 0; row < cvData.m_row ; row ++)
	{
		for (int column = 0; column < cvData.m_column; column ++)
		{
			int index = column + row * cvData.m_column;
			
			osg::Vec4 colorVal = ColorMgr::getInstance()->getColorByValue(cvData.m_data[index]);
			
			float alphaVal = m_dalphaVal;
			if (cvData.m_data[index] <= INVALIDE_MIN_VALUE || 
				cvData.m_data[index] <= m_dThresholdValue)
			{
				alphaVal = 0.0f;
			}
			destData._arrColor->push_back(osg::Vec4(colorVal.x(), colorVal.y(), colorVal.z(), alphaVal));
			destData._arrColor->push_back(osg::Vec4(colorVal.x(), colorVal.y(), colorVal.z(), alphaVal));
			destData._arrColor->push_back(osg::Vec4(colorVal.x(), colorVal.y(), colorVal.z(), alphaVal));
			destData._arrColor->push_back(osg::Vec4(colorVal.x(), colorVal.y(), colorVal.z(), alphaVal));

			{
				const double hei = cvData.m_heigh;
				const double lon = cvData.m_lon + column * cvData.m_ratio;
				const double lat = cvData.m_lat - row * cvData.m_ratio;
				osg::Vec3d xyz(lon, lat, hei);
				_converLonLatheiConvertXYZ(xyz, xyz);		
				destData._arrVertex3D->push_back(xyz);
				destData._arrVertex2D->push_back(osg::Vec3(lon,lat,0.001));
			}

			{
				const double hei = cvData.m_heigh;
				const double lon = cvData.m_lon + column*cvData.m_ratio;
				const double lat = cvData.m_lat - (row+1)*cvData.m_ratio;
				
				osg::Vec3d xyz(lon, lat, hei);
				_converLonLatheiConvertXYZ(xyz, xyz);
				destData._arrVertex3D->push_back(xyz);
				destData._arrVertex2D->push_back(osg::Vec3(lon,lat,0.001));

			}
			
			{
				const double hei = cvData.m_heigh;
				const double lon = cvData.m_lon + (column + 1) * cvData.m_ratio;
				const double lat = cvData.m_lat - (row+1) * cvData.m_ratio;

				osg::Vec3d xyz(lon, lat, hei);
				_converLonLatheiConvertXYZ(xyz, xyz);
				destData._arrVertex3D->push_back(xyz);
				destData._arrVertex2D->push_back(osg::Vec3(lon,lat,0.001));

			}

			{
				const double hei = cvData.m_heigh;
				const double lon = cvData.m_lon + (column+1) * cvData.m_ratio;
				const double lat = cvData.m_lat - row * cvData.m_ratio;

				osg::Vec3d xyz(lon, lat, hei);
				_converLonLatheiConvertXYZ(xyz, xyz);
				destData._arrVertex3D->push_back(xyz);
				destData._arrVertex2D->push_back(osg::Vec3(lon,lat,0.001));
			}
		}
	}

	cvData.release();
	return true;
}

void CEMDataCaching::_converLonLatheiConvertXYZ( const osg::Vec3d& lonLathei, osg::Vec3d& xyz )
{
	/*osg::EllipsoidModel ellND;
	
	ellND.convertLatLongHeightToXYZ(
		osg::DegreesToRadians(lonLathei.y()),
		osg::DegreesToRadians(lonLathei.x()),lonLathei.z(),
		xyz.x(), xyz.y(), xyz.z());*/
}

