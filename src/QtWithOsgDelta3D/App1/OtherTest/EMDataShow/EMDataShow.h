#ifndef EMDataShow_h__
#define EMDataShow_h__

#include <QObject>
//#include <VRMainFrame/mainwindow.h>
#include <QShortcut>
#include "EMDataShowDef.h"
#include <QSet>


class CEMDataCaching;
class CEMDataShow : public QObject
{
	Q_OBJECT
public:
   explicit CEMDataShow(QObject* pParent = NULL);
   virtual ~CEMDataShow();

public:
	bool setListEMData(const EMShowDef::ListEMDataFileInfo& listFileInfo);

	bool showEMFileData(const EMShowDef::EMDataFileInfo& info, bool b3D = true);

	bool removeEMShow(const EMShowDef::EMDataFileInfo& info, bool b3D);

	void clearNodes();

	bool reset();

	bool getShowState() const { return m_bShowState; }
	void setShowState(bool val);

	bool get3DSinglePicture() const { return m_b3DSinglePicture; }
	void set3DSinglePicture(bool val);

	void setThresholdValue(double val);
	void setShowHeightScale(int val);
	void setAlphaVal(double val);
protected Q_SLOTS:
	void slotNewMapOpen();
	void slotEMDataReaded(const QString& strID);
private:
	bool _showEMData(const QSharedPointer<EMShowDef::EMDataInfo>& data, bool b3D = true);

	void _removeChildFromLayersGroup( const std::string& idStr , bool is3D);

	void _clear3D();
	void _clear2D();
private:
	bool				m_bShowState;
	bool				m_b3DSinglePicture;		//3D只显示一张图片

	//osg::ref_ptr<osg::Group> m_heiLayersGroup3D;
	//osg::ref_ptr<osg::Group> m_heiLayersGroup2D;

	bool	m_bInit;

	//VRMainFrame::MainWindow* m_mainWindow;

	CEMDataCaching*		m_pEMDataCaching;

	QString			m_strCurDisplayedEMDataID_3D;
	QString			m_strCurDisplayedEMDataID_2D;

	bool	m_bWaitingShow3D;
	bool	m_bWaitingShow2D;
};


#endif // EMDataShow_h__
