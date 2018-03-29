#ifndef EMDataSelectWidget_h__
#define EMDataSelectWidget_h__

#include <QDateTime>
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include "EMDataShowDef.h"

class CEMDataShow;
class CEMDataSelectWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CEMDataSelectWidget(CEMDataShow* pShowInterface, QWidget *parent = 0);
    ~CEMDataSelectWidget();


protected Q_SLOTS:
	void slotOpenFolder();
	void slot3dToggled(bool btoggle);
	void slot2dToggled(bool btoggle);
	void slot3dChecked(int nState);
	void slotDoubleClicked(const QModelIndex & index);
protected:
	//QSize sizeHint()const{return QSize(400, 300);}
	void _init();
	
	void _refreshData();

	int _insert2Table(const QDateTime& dt, const EMShowDef::FolderFilesProperty& strDate, int nInsertRow = -1);

	bool _readAllDateTimeFolderFilesProperty( const QString& strCalcResultFolder, 
		EMShowDef::MapDateTimeFolderFilesProperty& mapFolderFilesProperty, 
		const QString& strExt,
		bool bActorID = false);

	bool _AnalyseFileName(const QString& strFileName, QString& strActorID, double& nHeight, int& nDataType, double& dFreq);

	void _defaultShowFirstRow();

	void _refresh3DCtrls(const QStringList& heightsStrings, bool bEnables = true);
	void _refresh2DCtrls(const QStringList& heightsStrings, bool bEnables = true);
	bool _showFileInfoData(const double& dHeight, bool is3D, bool bShow = true);
private:
    CEMDataShow*		m_pEMDataShow;

	QStandardItemModel	*m_pModel;
	QTableView			*m_pView;
	QModelIndex			m_indexCurDoubleClick;
	QDateTime			m_dtSelect;
	QDateTime			m_dtOld;

	QHBoxLayout*		m_playOutFor3D;
	QHBoxLayout*		m_playOutFor2D;
	QList<QCheckBox*>	m_list3DCheckBoxSelect;
	QList<QRadioButton*>	m_list3DRadioButtonSelect;
	QList<QRadioButton*>	m_list2DRadioButtonSelect;

	QLineEdit*			m_pLineEditFolder;

	EMShowDef::MapDateTimeFolderFilesProperty	m_mapTimeFolder;

	enum ViewColume
	{
		VC_Date,
		VC_HeightInfo
	};
};

#endif // EMDataSelectWidget_h__
