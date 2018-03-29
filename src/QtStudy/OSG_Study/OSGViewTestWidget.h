#ifndef OSGViewTestWidget_h__
#define OSGViewTestWidget_h__

#include <QWidget>
#include <QList>
#include <QMap>
#include <QDebug>
#include <assert.h>
#include <QHBoxLayOut>
#include <QVBoxLayOut>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>

namespace Ui 
{
	class OSGViewTestWidget;
}

class ViewerWidget;
class OSGViewTestWidget : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	OSGViewTestWidget(QWidget* parent = NULL);
	~OSGViewTestWidget();

public:
	
protected Q_SLOTS:
	void slotChangeOSgFile();
	void slotPathLineRect();
protected:

private:
	Ui::OSGViewTestWidget* m_pUI;

	ViewerWidget* m_pViewerWidget;
};

#endif // OSGViewTestWidget_h__
