#ifndef PictureTableView_h__
#define PictureTableView_h__

#include <QTableView>
#include <QAbstractItemModel>
#include <QWidget>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include <QComboBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QHeaderView>
#include <QMimeData>
#include <QDrag>
#include "PicToolDef.h"

#define PIC_ICON_SIZE 48
#define PIC_ICON_WIDTH 48
#define PIC_ICON_HEIGHT 48
#define ROW_HEIGHT 56
#define COLUME_WIDTH 200
#define MAX_COLUME_COUNT 1
static const QString& g_strPictureMimeType = QStringLiteral("PictureTableView/ModelUnitInfo");
extern QDataStream & operator>> (QDataStream& stream, ModelUnitInfo& dest);

class PictureTableView;
class PictureModel : public QAbstractTableModel
{  
	Q_OBJECT  
public:  
	PictureModel(PictureTableView *parent);

	void setModelListInfo(const ListModelUnitInfo& listDatas);

	bool resetModel();
	
	void refreshView();
public:
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	bool setData( const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */ );

	int rowCount(const QModelIndex &parent) const;

	int columnCount(const QModelIndex &parent) const;

	QVariant headerData(int section, Qt::Orientation orientation,int role) const;

	bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role /* = Qt::EditRole */){return false;}

	Qt::ItemFlags flags(const QModelIndex &index) const;


private:
	int _index(const QModelIndex &index)const;

	bool _indexValid(const QModelIndex &index)const;

	int _columeCount()const;
private:
	ListModelUnitInfo	_ListModelUnitInfo;
	mutable bool		_bInteRows;

private:
	PictureTableView*	_pView;
};

class Picturedeleget : public QItemDelegate
{
	Q_OBJECT
public:
	Picturedeleget();
	~Picturedeleget(){}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)const;
	bool editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index );
	void updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};

class PictureTableView : public QTableView
{
	Q_OBJECT
public:
	PictureTableView(QWidget* parent);
	~PictureTableView();

	void setTypeModelListInfo(const TypeModelListInfo& info);
protected:
	void resizeEvent(QResizeEvent *event);

protected Q_SLOTS:
	void slotPressed( const QModelIndex &index);
private:
	Picturedeleget* m_pPicturedeleget;
	PictureModel*	m_pPictureModel;
	TypeModelListInfo	m_TypeModelListInfo;
};



#endif // UIItemModel_h__
