#ifndef EMDataCaching_h__
#define EMDataCaching_h__

#include <QObject>
#include <QShortcut>
#include "EMDataShowDef.h"
#include <QSet>
#include <QFutureWatcher>
#include <QThread>

//#define USE_SHARED_PTR

class CEMDataCaching : public QThread
{
	Q_OBJECT
Q_SIGNALS:
	void singalEMDataReaded(const QString& strID);

public:
   explicit CEMDataCaching(QObject* pParent = NULL);
   virtual ~CEMDataCaching();

public:
	bool setListEMData(const EMShowDef::ListEMDataFileInfo& listFileInfo);

	bool setEMData(const EMShowDef::EMDataFileInfo& fileInfo);

	bool existEMData(const QString& strID);

	bool getEMData(const QString& strID, QSharedPointer<EMShowDef::EMDataInfo>& destData);

	bool removeEMData(const QString& strID);

	bool reset();
	
	double getThresholdValue() const { return m_dThresholdValue; }
	void setThresholdValue(double val) { m_dThresholdValue = val; }

	int getShowHeightScale() const { return m_nShowHeightScale; }
	void setShowHeightScale(int val) { m_nShowHeightScale = val; }

	double getAlphaVal() const { return m_dalphaVal; }
	void setAlphaVal(double val) { m_dalphaVal = val; }

	double getMaxValue() const { return m_dMaxValue; }
	double getMinValue() const { return m_dMinValue; }
protected:
	void run();
	bool _setEMData(const EMShowDef::EMDataFileInfo& fileInfo, bool bLock = true);
protected Q_SLOTS:
	void slotResultReadyAt(int nIndex);
	void slotFinished();

protected:
#ifdef USE_SHARED_PTR
	static QSharedPointer<EMShowDef::EMDataInfo> convertData(const EMShowDef::EMDataFileInfo& srcData);
#else
	static EMShowDef::EMDataInfo* convertData(const EMShowDef::EMDataFileInfo& srcData);
#endif

private:
	EMShowDef::EMDataInfo* _convertData(const EMShowDef::EMDataFileInfo& srcData);

	bool _readCoverageFile( const QString& dataFilePath, 
		EMShowDef::coverageResultData& data );
	
	bool _convertCoverLayerData(
		const EMShowDef::coverageResultData& data , 
		EMShowDef::EMDataInfo& destData);

	bool _updateMaxMinValue(double dMax, double dMin);

	void _converLonLatheiConvertXYZ( const osg::Vec3d& lonLathei, osg::Vec3d& xyz );
private:
	double				m_dalphaVal;			//透明度

	double				m_dThresholdValue;	//门限值
	int					m_nShowHeightScale;	//高度值放大倍数

	double				m_dMaxValue;	//最大值
	double GetMaxValue() const { return m_dMaxValue; }
	void SetMaxValue(double val) { m_dMaxValue = val; }
	double				m_dMinValue;	//最小值
	double GetMinValue() const { return m_dMinValue; }
	void SetMinValue(double val) { m_dMinValue = val; }
	QMutex				m_mutexMaxMin;

	QMutex		m_mutex;
	EMShowDef::ListEMDataFileInfo	m_listFileInfo;
	EMShowDef::ListEMDataFileInfo	m_TempList;
#ifdef USE_SHARED_PTR
	QFutureWatcher<QSharedPointer<EMShowDef::EMDataInfo>> m_watcher;
#else
	QFutureWatcher<EMShowDef::EMDataInfo*> m_watcher;
#endif
	QMutex				m_mutexMapCachedEMData;
	EMShowDef::MapCachedEMData	m_mapCachedData;
	int			m_nMaxCacheSize;

	volatile bool	m_bRunning;

};

#endif // EMDataCaching_h__
