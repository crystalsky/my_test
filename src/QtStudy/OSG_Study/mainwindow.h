#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <CenterActionStackWidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
	void closeEvent(QCloseEvent *e);

protected Q_SLOTS:
	void slotActionTriggered(QAction* pAction);
private:
	void _readSetting();
	void _saveSetting();
	void _createMenu();
	void _createMenuActions();

	bool _addActionToMenu(QAction* pAction, QMenu* pMenu);
private:
    Ui::MainWindow *ui;
	QString m_strLastAction;
	CenterActionStackWidget*	m_pCenterActionStackWidget;

	QMenu*		m_pMenu_OSGBooks;
	QMenu*		m_pMenu_OSGProgramingGuid;
};

#endif // MAINWINDOW_H
