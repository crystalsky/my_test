#ifndef widget_QtGuiStudy_h__
#define widget_QtGuiStudy_h__

#include <QList>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
//! [0]
class CWidget_QMLGui : public QWidget
{
public:
	CWidget_QMLGui(QWidget* pParent = NULL);
	~CWidget_QMLGui();
protected:
	void init();
	virtual void showEvent(QShowEvent *e);
private:
	QTabWidget*		m_pTabWidget;
	bool m_bInit;
};

#endif // widget_QtGuiStudy_h__
