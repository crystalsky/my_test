#include "EMDataSelectWidget.h"
#include "EMDataShow.h"
#include <QDir>
#include <QFileDialog>
#include <QApplication>
#include <QCoreApplication>
#include <QMessageBox>
#include <assert.h>

CEMDataSelectWidget::CEMDataSelectWidget(CEMDataShow* pShowInterface, QWidget *parent)
	: QDialog(parent)
	, m_pModel(NULL)
	, m_pEMDataShow(pShowInterface)
{
	assert(m_pEMDataShow != NULL);

	setWindowTitle(QStringLiteral("电磁数据列表显示"));

	_init();

	resize(500, 400);
}

CEMDataSelectWidget::~CEMDataSelectWidget()
{
	
}

void CEMDataSelectWidget::_init()
{
	QVBoxLayout* pLayAll = new QVBoxLayout;
	{
		QGroupBox* pGroupBox = new QGroupBox(this);
		QHBoxLayout* play = new QHBoxLayout(pGroupBox);

		QLabel* pLable = new QLabel(QStringLiteral("数据文件夹设置："), pGroupBox);
		
		m_pLineEditFolder = new QLineEdit(pGroupBox);
		m_pLineEditFolder->setReadOnly(true);

		QPushButton* pButton = new QPushButton(QStringLiteral("..."), pGroupBox);
		pButton->setFixedSize(pButton->height(), pButton->height());
		connect(pButton, SIGNAL(clicked()), SLOT(slotOpenFolder()));
		play->addWidget(pLable);
		play->addWidget(m_pLineEditFolder);
		play->addWidget(pButton);

		pLayAll->addWidget(pGroupBox);
	}

	{
		QGroupBox* pGroupBox = new QGroupBox(QStringLiteral("数据信息"), this);
		QVBoxLayout* play = new QVBoxLayout(pGroupBox);

		m_pView = new QTableView(pGroupBox);
		m_pModel = new QStandardItemModel(this);

		QStringList listHeaderLabels;
		listHeaderLabels 
			<< QStringLiteral("日期")
			<< QStringLiteral("数据信息");

		m_pModel->setHorizontalHeaderLabels(listHeaderLabels);

		m_pView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_pView->setSelectionMode(QAbstractItemView::SingleSelection);
		m_pView->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_pView->setModel(m_pModel);
		m_pView->setMinimumSize(300, 210);

		m_pView->setColumnWidth(VC_Date, 100);
		m_pView->setColumnWidth(VC_HeightInfo, 230);

		connect(m_pView, SIGNAL(doubleClicked(const QModelIndex &)),
			SLOT(slotDoubleClicked(const QModelIndex &)));

		play->addWidget(m_pView);

		pLayAll->addWidget(pGroupBox);
	}

	{
		QGroupBox* pGroupBox = new QGroupBox(QStringLiteral("3D/2D数据展示选择"), this);
		QVBoxLayout* playGroup = new QVBoxLayout(pGroupBox);
		
		QGroupBox* pGroupBox3D = new QGroupBox(QStringLiteral("3D展示选择"), pGroupBox);
		m_playOutFor3D = new QHBoxLayout(pGroupBox3D);
		QLabel* plab3d = new QLabel(QStringLiteral("3D展示数据选择："));
		m_playOutFor3D->addWidget(plab3d);

		QGroupBox* pGroupBox2D = new QGroupBox(QStringLiteral("3D展示选择"), pGroupBox);
		m_playOutFor2D = new QHBoxLayout(pGroupBox2D);
		QLabel* plab2d = new QLabel(QStringLiteral("2D展示数据选择："));
		m_playOutFor2D->addWidget(plab2d);

		playGroup->addWidget(pGroupBox3D);
		playGroup->addWidget(pGroupBox2D);

		QStringList list;
		list << QStringLiteral("1000m")
			<< QStringLiteral("2000m")
			<< QStringLiteral("3000m");
		_refresh3DCtrls(list, false);
		_refresh2DCtrls(list, false);

		pLayAll->addWidget(pGroupBox);
	}

	setLayout(pLayAll);
}

void CEMDataSelectWidget::_refresh3DCtrls( const QStringList& heightsStrings, bool bEnables /*= true*/ )
{
	if (!m_pEMDataShow)
	{
		return;
	}

	for (int i = 0; i < m_list3DRadioButtonSelect.size(); ++i)
	{
		QRadioButton* pbutton = m_list3DRadioButtonSelect[i];
		m_playOutFor3D->removeWidget(pbutton);
		pbutton->close();
	}
	m_list3DRadioButtonSelect.clear();

	for (int i = 0; i < m_list3DCheckBoxSelect.size(); ++i)
	{
		QCheckBox* pbutton = m_list3DCheckBoxSelect[i];
		m_playOutFor3D->removeWidget(pbutton);
		pbutton->close();
	}
	m_list3DCheckBoxSelect.clear();

	if (m_pEMDataShow->get3DSinglePicture())
	{
		for (int  i = 0; i < heightsStrings.size(); ++i)
		{
			const QString& strH = heightsStrings[i];
			QRadioButton* pButton = new QRadioButton(QString("%1m").arg(strH));

			pButton->setObjectName(strH);
			pButton->setAttribute(Qt::WA_DeleteOnClose);
			connect(pButton, SIGNAL(toggled(bool)), SLOT(slot3dToggled(bool)));

			m_playOutFor3D->addWidget(pButton);
			pButton->setEnabled(bEnables);

			m_list3DRadioButtonSelect << pButton;
		}
	}
	else
	{
		for (int  i = 0; i < heightsStrings.size(); ++i)
		{
			const QString& strH = heightsStrings[i];
			QCheckBox* pButton = new QCheckBox(QString("%1m").arg(strH));

			pButton->setAttribute(Qt::WA_DeleteOnClose);
			pButton->setObjectName(strH);
			connect(pButton, SIGNAL(stateChanged(int)), SLOT(slot3dChecked(int)));
			m_playOutFor3D->addWidget(pButton);
			pButton->setEnabled(bEnables);

			m_list3DCheckBoxSelect << pButton;
		}
	}
}

void CEMDataSelectWidget::_refresh2DCtrls( const QStringList& heightsStrings, bool bEnables /*= true*/ )
{
	for (int i = 0; i < m_list2DRadioButtonSelect.size(); ++i)
	{
		QRadioButton* pbutton = m_list2DRadioButtonSelect[i];
		m_playOutFor2D->removeWidget(pbutton);
		pbutton->close();
	}
	m_list2DRadioButtonSelect.clear();

	for (int  i = 0; i < heightsStrings.size(); ++i)
	{
		const QString& strH = heightsStrings[i];
		QRadioButton* pButton = new QRadioButton(QString("%1m").arg(strH));
		pButton->setObjectName(strH);
		pButton->setAttribute(Qt::WA_DeleteOnClose);

		connect(pButton, SIGNAL(toggled(bool)), SLOT(slot2dToggled(bool)));

		m_playOutFor2D->addWidget(pButton);
		pButton->setEnabled(bEnables);

		m_list2DRadioButtonSelect << pButton;
	}

	if (!m_mapTimeFolder.isEmpty() && !m_list2DRadioButtonSelect.isEmpty())
	{
		m_list2DRadioButtonSelect.front()->toggle();
	}
}

void CEMDataSelectWidget::slotOpenFolder()
{
	const QString dir = QFileDialog::getExistingDirectory(this, QStringLiteral("选择电磁数据文件夹"), 
		QCoreApplication::applicationDirPath(),
		QFileDialog::ShowDirsOnly);
	if (dir.isEmpty())
	{
		QMessageBox::warning(this, QStringLiteral("提示:"), QStringLiteral("打开文件夹失败"));
		return;
	}

	m_pLineEditFolder->setText(dir);
	if (!_readAllDateTimeFolderFilesProperty(dir, m_mapTimeFolder, ".rdt"))
	{
		QMessageBox::warning(this, QStringLiteral("提示:"), QStringLiteral("此文件下不含有电磁计算数据!"));
		return;
	}

	if (m_pEMDataShow)
	{
		m_pEMDataShow->reset();
	}

	_refreshData();
}

bool CEMDataSelectWidget::_readAllDateTimeFolderFilesProperty( 
	const QString& strCalcResultFolder, 
	EMShowDef::MapDateTimeFolderFilesProperty& mapFolderFilesProperty,
	const QString& strExt,
	bool bActorID)
{
	if (strCalcResultFolder.isEmpty())
	{
		return false;
	}

	QDir dir(strCalcResultFolder);

	if(!dir.exists())
	{
		QString strMsg = QString("Folder Not Exist:%1").arg(strCalcResultFolder);
		return false;
	}

	QStringList timeTickFolder = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

	for (int i = 0; i < timeTickFolder.size(); ++i)
	{
		EMShowDef::FolderFilesProperty property;

		property.strFolderName		= timeTickFolder[i];
		property.strFolderFullPath	= QString("%1/%2").arg(strCalcResultFolder).arg(property.strFolderName);

		const QDateTime datetime = QDateTime::fromString(property.strFolderName, EMShowDef::CALC_RESULT_TIME_TICK_FORMAT);

		if (datetime.isNull() || !datetime.isValid())
		{
			continue;
		}

		QFileInfoList listFiles = QDir(property.strFolderFullPath).entryInfoList(QDir::Files, QDir::Name);
		foreach (QFileInfo info, listFiles)
		{
			const QString strFileFullPath = info.filePath();
			if (!strExt.isEmpty() && !strFileFullPath.contains(strExt))
			{
				continue;
			}
			
			EMShowDef::EMDataFileInfo resultPro;
			resultPro._strFileFullPath = strFileFullPath;
			resultPro._strFileName = strFileFullPath.right(strFileFullPath.length() - strFileFullPath.lastIndexOf('/') - 1);
			resultPro._dateTime = datetime;

			QString strActorID;
			_AnalyseFileName(resultPro._strFileName, strActorID, resultPro._dHeight, resultPro._nDataType, resultPro._dFrequency);

			if (bActorID && !strActorID.isEmpty())
			{
				property.listResultFilesPro << resultPro;
			}
			else if(!bActorID && strActorID.isEmpty() && !CHECK_DOUBLE_EQUAL(resultPro._dHeight, 0))
			{
				property.listResultFilesPro << resultPro;
			}
		}

		mapFolderFilesProperty.insert(datetime, property);

	}

	return !mapFolderFilesProperty.isEmpty();
}

bool CEMDataSelectWidget::_AnalyseFileName( const QString& strFileName, QString& strActorID, double& nHeight, int& nDataType, double& dFreq )
{
	if (strFileName.isEmpty())
	{
		return false;
	}

	const QString strTemp = strFileName.left(strFileName.lastIndexOf('.'));

	QStringList listSplit = strTemp.split('_');
	//角色编号_高度_数据类型
	if (listSplit.size() != 4)
	{
		return false;
	}

	strActorID = listSplit[0];
	nHeight = listSplit[1].toDouble();
	//nDataType = GetFileType(listSplit[2]);
	//dFreq = listSplit[3].toULongLong() * HZ_2_MHZ;

	return true;
}

void CEMDataSelectWidget::_refreshData()
{
	if (!m_pModel)
	{
		return;
	}
	m_pModel->setRowCount(0);

	QMapIterator<QDateTime, EMShowDef::FolderFilesProperty> iter(m_mapTimeFolder);
	while(iter.hasNext())
	{
		const EMShowDef::FolderFilesProperty &pro = iter.next().value();

		_insert2Table(iter.key(), iter.value());
	}

	if (!m_mapTimeFolder.isEmpty())
	{
		_defaultShowFirstRow();
	}
}

void CEMDataSelectWidget::_defaultShowFirstRow()
{
	m_pView->selectRow(0);
	slotDoubleClicked(m_pModel->index(0, 0));
}

void CEMDataSelectWidget::slotDoubleClicked( const QModelIndex & index )
{
	if (!index.isValid())
	{
		return;
	}
	m_indexCurDoubleClick = index;

	QModelIndex indexColume = m_pModel->index(index.row(), VC_Date);
	m_dtSelect = m_pModel->data(indexColume, Qt::UserRole).toDateTime();
	
	if (m_dtOld != m_dtSelect)
	{
		m_pEMDataShow->clearNodes();
		m_dtOld = m_dtSelect;
	}

	//缓存
	const EMShowDef::FolderFilesProperty & filesProperty = m_mapTimeFolder.value(m_dtSelect);
	m_pEMDataShow->setListEMData(filesProperty.listResultFilesPro);

	indexColume = m_pModel->index(0, VC_HeightInfo);
	QStringList listHeights = m_pModel->data(indexColume, Qt::UserRole).toStringList();
	if (listHeights.isEmpty())
	{
		return;
	}
	
	{
		_refresh3DCtrls(listHeights);

		if (m_pEMDataShow->get3DSinglePicture())
		{
			if (!m_mapTimeFolder.isEmpty() && !m_list3DRadioButtonSelect.isEmpty())
			{
				m_list3DRadioButtonSelect.front()->toggle();
			}
		}
		else
		{
			if (!m_mapTimeFolder.isEmpty() && !m_list3DCheckBoxSelect.isEmpty())
			{
				m_list3DCheckBoxSelect.front()->setChecked(true);
			}
		}
	}
	
	{
		_refresh2DCtrls(listHeights);
		if (!m_mapTimeFolder.isEmpty() && !m_list2DRadioButtonSelect.isEmpty())
		{
			m_list2DRadioButtonSelect.front()->toggle();
		}
	}

	
}

int CEMDataSelectWidget::_insert2Table(const QDateTime& dt, const EMShowDef::FolderFilesProperty& info, int nInsertRow )
{
	int nRow = 0;

	if (nInsertRow == -1)
	{
		m_pModel->appendRow(NULL);
		nRow = m_pModel->rowCount() - 1;
	}
	else
	{
		m_pModel->insertRow(nInsertRow, NULL);
		nRow = nInsertRow;
	}

	QString strHeightInfo(QStringLiteral("结果高度信息:"));
	QStringList listHeights;
	for (int i = 0; i < info.listResultFilesPro.size(); ++i)
	{
		const QString strHeight = QString("%1m").arg((int)info.listResultFilesPro.at(i)._dHeight);
		if (i != info.listResultFilesPro.size() - 1)
		{
			strHeightInfo = strHeightInfo + strHeight + QStringLiteral("、");
		}
		else
		{
			strHeightInfo = strHeightInfo + strHeight;
		}
		
		listHeights << QString("%1").arg((int)info.listResultFilesPro.at(i)._dHeight);
	}

	m_pModel->setData(m_pModel->index(nRow, VC_Date), dt, Qt::UserRole);
	m_pModel->setData(m_pModel->index(nRow, VC_Date), dt.toString(EMShowDef::LIST_TIME_TICK_FORMAT), Qt::ToolTipPropertyRole);
	m_pModel->setData(m_pModel->index(nRow, VC_Date), dt.toString(EMShowDef::LIST_TIME_TICK_FORMAT));
	
	m_pModel->setData(m_pModel->index(nRow, VC_HeightInfo), listHeights, Qt::UserRole);
	m_pModel->setData(m_pModel->index(nRow, VC_HeightInfo), strHeightInfo, Qt::ToolTipPropertyRole);
	m_pModel->setData(m_pModel->index(nRow, VC_HeightInfo), strHeightInfo);

	for (int nColume = 0; nColume < m_pModel->columnCount(); ++nColume)
	{
		m_pModel->item(nRow, nColume)->setEditable(false);
	}

	return nRow;
}

void CEMDataSelectWidget::slot3dToggled( bool btoggle )
{
	QRadioButton* pradio = qobject_cast<QRadioButton*>(sender());
	if (!pradio)
	{
		return;
	}

	if (!_showFileInfoData(pradio->objectName().toDouble(), true))
	{

	}
}

void CEMDataSelectWidget::slot2dToggled( bool btoggle )
{
	QRadioButton* pradio = qobject_cast<QRadioButton*>(sender());
	if (!pradio)
	{
		return;
	}

	if (!_showFileInfoData(pradio->objectName().toDouble(), false))
	{

	}
}

void CEMDataSelectWidget::slot3dChecked( int nState )
{
	QCheckBox* pCheck = qobject_cast<QCheckBox*>(sender());
	if (!pCheck)
	{
		return;
	}

	if (!_showFileInfoData(pCheck->objectName().toDouble(), true, nState == Qt::Checked))
	{

	}
}

bool CEMDataSelectWidget::_showFileInfoData(const double& dHeight, bool is3D, bool bShow)
{
	if(!m_pEMDataShow || !m_mapTimeFolder.contains(m_dtSelect))
	{
		return false;
	}

	const EMShowDef::FolderFilesProperty & filesProperty = m_mapTimeFolder.value(m_dtSelect);
	EMShowDef::EMDataFileInfo file = filesProperty.getEMDataByHeight(dHeight);
	if (!file.valid())
	{
		return false;
	}

	if (!bShow)
	{
		return m_pEMDataShow->removeEMShow(file, is3D);
	}

	return m_pEMDataShow->showEMFileData(file, is3D);
}
