#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QStackedWidget>
#include "qtoolbox.h"

QT_BEGIN_NAMESPACE
class QAction;
class QListWidget;
class QMenu;
class QTextEdit;
QT_END_NAMESPACE

//! [0]
class CEMDataShow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
	void closeEvent(QCloseEvent *e);
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
private slots:
    void about();
	void slotAction();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();

	void initFunctionalWidgets();
	void _readSetting();
	void _saveSetting();
	void _startLastAction();

	QAction* _addFunctionAction(QWidget* pWidget, const QString& strActionName, const QIcon& icon = QIcon());

	QListWidget *customerList;
    QListWidget *paragraphsList;

	QStackedWidget*		m_pCenterWidget;

	QMenu*		m_pMenu_QML;
	QMenu*		m_pMenu_QtGUI;
	QMenu*		m_pMenu_QtCore;
	QMenu*		m_pMenu_Boost;
	QMenu*		m_pMenu_Stl;
	QMenu*		m_pMenu_OtherTest;
	QMap<QAction*, QWidget*>		m_mapFunctionalWidget;

	QString		m_strLastAction;

	//
	CEMDataShow*				m_pEMDataShow; 
};
//! [0]

#endif
