#ifndef ServeDialog_h__
#define ServeDialog_h__

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include "XMLCfg_UDPServer.h"
#include "CDataProc.h"

namespace Ui {
class ServerDialog;
}
class CDynamicUIWidget;
class CServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CServerDialog(QWidget *parent = 0);
    ~CServerDialog();

protected Q_SLOTS:
	void _slotTimerSendData();
	void _slotDynamicUI();
protected:
	bool _readXMLConfig();
	bool _initTabWidget();
private:
    Ui::ServerDialog *	ui;

	UDPServerCfg mUDPServerCfg;

	CDataProc*	m_pServer;
	CDataProc*	m_pClient;

	QTimer*		m_pTimer;

	CDynamicUIWidget*	m_pDynamicUIWidget;
};

#endif // ServeDialog_h__
