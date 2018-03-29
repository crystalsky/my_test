#include "ServerDialog.h"
#include "ui_ServerDialog.h"
#include "PlaneServer.h"
#include "FacilityServer.h"
#include "qtabwidget.h"
#include "UIItem_Page.h"
#include <QLibrary>
#include <QShortcut>
#include "DynamicUIWidget.h"

#define TEST_SERVER_PORT 8000
#define TEST_CLIENT_PORT 8001

CServerDialog::CServerDialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::ServerDialog)
	, m_pDynamicUIWidget(NULL)
{
    ui->setupUi(this);
	setObjectName("CServerDialog");
	ui->tabWidget->clear();

	QShortcut* pShortCut = new QShortcut(Qt::Key_F12, this);
	connect(pShortCut, SIGNAL(activated()), this, SLOT(_slotDynamicUI()));

	
	/*m_pServer = new CDataProc;
	m_pClient = new CDataProc;
	
	m_pTimer = new QTimer(this);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(_slotTimerSendData()));
	
	if (!m_pServer->Init(TEST_SERVER_PORT, "192.168.0.61", TEST_CLIENT_PORT))
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("提示:"), 
			QString("m_pServer Init Failed"));
	}
	if (!m_pClient->Init(TEST_CLIENT_PORT, "192.168.0.61", TEST_SERVER_PORT))
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("提示:"), 
			QString("m_pClient Init Failed"));
	}
	m_pClient->Start();
	m_pServer->Start();

	m_pTimer->start(1000);*/

	if (_readXMLConfig())
	{
		_initTabWidget();
	}
}

CServerDialog::~CServerDialog()
{
    delete ui;
}

void CServerDialog::_slotTimerSendData()
{
	static qlonglong nCurIndex = 0;
	QString strdata;
	for (int i = 0; i < 100; ++i)
	{
		const QString str =  QString("[%1]:123456789").arg(i, 4);
		strdata += str;
	}

	QByteArray datagram;
	QDataStream stream(&datagram, QIODevice::WriteOnly);
	stream.setVersion(QDataStream::Qt_5_3);

	int nDataSize = sizeof(nCurIndex) + strdata.length();

	stream << nDataSize;
	stream << nCurIndex;
	stream.writeRawData(strdata.toLocal8Bit().data(), strdata.length());
	const int nsize = datagram.size();

	m_pClient->SendData(datagram);
}

bool CServerDialog::_readXMLConfig()
{
	CXmlFileStream stream(QApplication::applicationDirPath() + "/../data/conf/" + "UDPServerCfg.xml");
	if(!(stream >> mUDPServerCfg))
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("提示:"), 
			QString(QString::fromLocal8Bit("读取配置文件 %1 失败!")).arg("UDPServerCfg.xml"));
		return false;
	}
	return true;
}

bool CServerDialog::_initTabWidget()
{
	for (int i = 0; i < mUDPServerCfg.mPlaneStateCfg.m_vecItem.size(); ++i)
	{
		const CommuItemCfg &item = mUDPServerCfg.mPlaneStateCfg.m_vecItem[i];
		CPlaneUDPServer* pServer = new CPlaneUDPServer(item, this);
		ui->tabWidget->addTab(pServer, item.m_info.strFacilityID);
	}

	for (int i = 0; i < mUDPServerCfg.mFacilityCfg.m_vecItem.size(); ++i)
	{
		const CommuItemCfg &item = mUDPServerCfg.mFacilityCfg.m_vecItem[i];
		CFacilityServer* pServer = new CFacilityServer(item, this);
		ui->tabWidget->addTab(pServer, item.m_info.strFacilityID);
	}

	return true;
}

void CServerDialog::_slotDynamicUI()
{
	if (m_pDynamicUIWidget == NULL)
	{
		m_pDynamicUIWidget = new CDynamicUIWidget();
	}

	m_pDynamicUIWidget->hide();
	m_pDynamicUIWidget->show();
}
