#ifndef widget_BoostStudy_h__
#define widget_BoostStudy_h__

#include <QList>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
//! [0]
namespace Study_Boost{
class CWidget_BoostStudy : public QWidget
{
public:
	CWidget_BoostStudy(QWidget* pParent = NULL);
	~CWidget_BoostStudy(){}
protected:
	void init();

private:
	QTabWidget*		m_pTabWidget;
};
}
//! [0]

#endif // widget_BoostStudy_h__
