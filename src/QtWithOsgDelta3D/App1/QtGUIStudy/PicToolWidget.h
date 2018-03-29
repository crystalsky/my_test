#ifndef PicToolWidget_h__
#define PicToolWidget_h__

#include <QToolBox>
#include <QVBoxLayout>
#include "PicToolDef.h"

class PicToolWidget : public QWidget
{
	Q_OBJECT
public:
	PicToolWidget(QWidget* pParnet = NULL);
	~PicToolWidget();

protected:
	void _init();

	void _readData();

	void _refreshPicToolBox();

protected:
	 bool eventFilter(QObject *obj, QEvent *event);

	 QSize sizeHint()const;
private:
	QToolBox*	m_pPicToolBox;

	ListTypeModelListInfo m_listAllPicModelInfo;
};

#endif // PicToolWidget_h__
