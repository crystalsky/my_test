#ifndef widget_QMLStudy_h__
#define widget_QMLStudy_h__

#include <QList>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
//! [0]
class CWidget_QMLStudy : public QWidget
{
public:
	CWidget_QMLStudy(QWidget* pParent = NULL);
	~CWidget_QMLStudy();
protected:
	void init();
	virtual void showEvent(QShowEvent *e);
protected:
	void test1() throw(std::runtime_error);
private:
	QTabWidget*		m_pTabWidget;
	bool m_binit;
};

//! [0]

#endif // widget_QMLStudy_h__
