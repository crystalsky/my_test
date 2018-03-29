#ifndef CFunctionOSGViewerWidget_h__
#define CFunctionOSGViewerWidget_h__

#include <QWidget>
#include <QList>
#include <QMap>
#include <QDebug>
#include <QLabel>
#include <QGroupBox>
#include <assert.h>
#include "osgviewerQt.h"
#include "StepBase.h"

class OSGFuncBase;
class CFunctionOSGViewerWidget : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	//信号
	
	
public:
	CFunctionOSGViewerWidget(QWidget* parent = NULL);
	CFunctionOSGViewerWidget(const QString& strTitle, QWidget* parent = NULL);
	CFunctionOSGViewerWidget(int nButtonColNum, QWidget* pParnet);
	CFunctionOSGViewerWidget(const QString& strTitle, int nButtonColNum, QWidget* pParnet);
	~CFunctionOSGViewerWidget();

public:
	void setLabelContent(const QString& strContents);
	void setTitle(const QString& strTitle);
	void setLayoutMainStrech(int strech1, int strech2);

	void setToDefaultViewerWidget();
protected Q_SLOTS:
	virtual void slotButtonClicked(const QString& strFunctionButtonName);

protected:
	bool addFunctional(const QString& strButtonName);
private:
	void _init(int nButtonColNum = 1);

	OSGFuncBase* _getOSGFuncBase(const QString& strFunctionButtonName);
protected:
	ViewerWidget* m_pViewerWidget;	//默认ViewerWidget
private:
	QtUI::CButtonFunctionWidget* m_pButtonFunctionWidget;
	
	QStackedWidget*	m_pStackedWidget;
	
	QGroupBox*	m_pGroupBox;
	QLabel*		m_pLabelTitle;
	QHBoxLayout*	m_pLayoutMain;

	QMap<QString, OSGFuncBase*>	m_mapNamedOSGFunc;
};

#endif // CFunctionOSGViewerWidget_h__
