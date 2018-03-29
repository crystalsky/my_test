#include "PictureTableView.h"
#include "glog.h"
#include <QScrollBar>

QDataStream & operator<< (QDataStream& stream, const ModelUnitInfo& src)
{
	stream << src.strID;
	stream << src.strIcon;
	stream << src.strModel;
	stream << src.strToolTip;
	stream << src.strName;
	stream << src.innerInfo.nType;
	stream << src.innerInfo.strTypeName;

	return stream;
}

QDataStream & operator>> (QDataStream& stream, ModelUnitInfo& dest)
{
	stream >> dest.strID;
	stream >> dest.strIcon;
	stream >> dest.strModel;
	stream >> dest.strToolTip;
	stream >> dest.strName;
	stream >> dest.innerInfo.nType;
	stream >> dest.innerInfo.strTypeName;

	return stream;
}

Picturedeleget::Picturedeleget()
{

}

void Picturedeleget::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index )const
{
	if (!index.isValid())
	{
		return;
	}

	const QAbstractItemModel* pModel = index.model();
	QVariant val = pModel->data(index, Qt::UserRole);
	QByteArray arr = val.toByteArray();
	if (arr.isEmpty())
	{
		return;
	}

	QDataStream stream(&arr, QIODevice::ReadOnly);
	ModelUnitInfo info;
	stream.setVersion(QDataStream::Qt_5_0);
	stream >> info;
	if (info.strIcon.isEmpty())
	{
		return;
	}

	QPixmap px;

	QFont font;
	font.setBold(true);
	font.setPixelSize(20);
	font.setFamily(QStringLiteral("¿¬Ìå"));
	QFontMetrics me(font);
	const QRectF textRect = me.boundingRect(info.innerInfo.strTypeName);

	if(!px.load(info.strIcon))
	{
		LOG(WARNING) << "Picturedeleget Load File" << val.toString().toLocal8Bit().data() << "Failed!";
	}
	else
	{
		const int nWidth = textRect.width() + px.width();
		const int nMaxPicWidth = option.rect.width() * 4 / 7;
		if (nWidth < COLUME_WIDTH)
		{

		}
		else
		{

		}
		
		QPointF pt;
		if (px.width() >= nMaxPicWidth)
		{
			pt.setX(0);
			px = px.scaledToWidth(nMaxPicWidth);
		}
		else
		{
			pt.setX(nMaxPicWidth / 2 - px.width() / 2);
		}

		if (px.height() >= option.rect.height())
		{
			pt.setY(0);
			px = px.scaledToHeight(option.rect.height());
		}
		else 
		{
			pt.setY(option.rect.height() / 2 - px.rect().height() / 2);
		}

		drawBackground(painter, option, index);
		
		painter->drawPixmap(option.rect.x() + pt.x(), option.rect.y() + pt.y(), px);
		
		painter->setFont(font);
		painter->drawText(
			option.rect.x() + nMaxPicWidth,
			option.rect.y(),
			option.rect.width() - nMaxPicWidth,
			option.rect.height(),
			Qt::AlignCenter,
			info.strName);

		drawFocus(painter, option, option.rect);
	}
}

bool Picturedeleget::editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index )
{
	return QItemDelegate::editorEvent(event, model, option, index);
}

void Picturedeleget::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}

PictureTableView::PictureTableView(QWidget* parent) : QTableView(parent)
{
	m_pPicturedeleget = new Picturedeleget();
	m_pPictureModel = new PictureModel(this);

	setModel(m_pPictureModel);
	setItemDelegate(m_pPicturedeleget);

	verticalHeader()->setVisible(false);
	verticalHeader()->setDefaultSectionSize(ROW_HEIGHT);
	verticalHeader()->setMinimumSectionSize(ROW_HEIGHT);
	verticalHeader()->setMaximumSectionSize(ROW_HEIGHT);
	
	horizontalHeader()->setVisible(false);
	horizontalHeader()->setDefaultSectionSize(COLUME_WIDTH);
	horizontalHeader()->setMinimumSectionSize(COLUME_WIDTH);
	horizontalHeader()->setMaximumSectionSize(COLUME_WIDTH);
	
	horizontalScrollBar()->setPageStep(COLUME_WIDTH);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setMouseTracking(true);

	setDragEnabled(true);

	connect(this, SIGNAL(pressed ( const QModelIndex & )), SLOT(slotPressed( const QModelIndex & ) ));
}

PictureTableView::~PictureTableView()
{

}

void PictureTableView::resizeEvent( QResizeEvent *event )
{
	m_pPictureModel->refreshView();
	QTableView::resizeEvent(event);
}

void PictureTableView::setTypeModelListInfo( const TypeModelListInfo& info )
{
	m_TypeModelListInfo = info;
	if (m_pPictureModel)
	{
		m_pPictureModel->setModelListInfo(info._listModelUnit);
	}
}

PictureModel::PictureModel( PictureTableView *parent/*=NULL*/ )
	: QAbstractTableModel(parent)
	, _bInteRows(false)
	, _pView(parent)
{

}

void PictureModel::setModelListInfo( const ListModelUnitInfo& listDatas )
{
	_ListModelUnitInfo = listDatas;

	refreshView();
}

void PictureModel::refreshView()
{
	beginResetModel();

	endResetModel();
}

int PictureModel::rowCount( const QModelIndex &parent ) const
{
	_bInteRows = _ListModelUnitInfo.size() % _columeCount() == 0;
	
	const int nR = _ListModelUnitInfo.size() / _columeCount();

	return _bInteRows ? nR : nR + 1;
}

int PictureModel::columnCount( const QModelIndex &parent ) const
{
	return _columeCount();
}

QVariant PictureModel::data( const QModelIndex &index, int role /*= Qt::DisplayRole*/ ) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if( Qt::TextAlignmentRole == role )  
		return Qt::AlignCenter;   
	else if (Qt::ToolTipPropertyRole == role)
	{
		const int nIndex = _index(index);
		if (nIndex < _ListModelUnitInfo.size())
		{
			return _ListModelUnitInfo[nIndex].strToolTip;
		}
	}
	else if (Qt::UserRole == role)
	{
		const int nIndex = _index(index);
		if (nIndex < _ListModelUnitInfo.size())
		{
			QByteArray arr;
			QDataStream stream(&arr, QIODevice::WriteOnly);
			stream.setVersion(QDataStream::Qt_5_0);
			stream << _ListModelUnitInfo.at(nIndex);

			return QVariant(arr);
		}
	}

	return QVariant();
}

bool PictureModel::setData( const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */ )
{
	/*if (index.isValid() && role == Qt::EditRole)
	{
		QModelIndex index = createIndex(index.column(), index.row());

		emit dataChanged(index, index);
		emit dataChanged()
	}*/
	return QAbstractTableModel::setData(index, value, role);
// 	if (role == Qt::UserRole)
// 	{
// 		const int nIndex = index.row() * VIEW_COLUME_COUNT + index.column();
// 		if (nIndex < _ListModelUnitInfo.size())
// 		{
// 			return QAbstractItemModel::setData(index, _ListModelUnitInfo[nIndex].strIcon, Qt::UserRole);
// 		}
// 	}
// 
// 	return false;
}

Qt::ItemFlags PictureModel::flags( const QModelIndex &index ) const
{
	Qt::ItemFlags flags = QAbstractItemModel::flags(index);
	if (_indexValid(index))
	{
		flags |= Qt::ItemIsDragEnabled;
	}

	return flags;
}

QVariant PictureModel::headerData( int section, Qt::Orientation orientation,int role )const
{
	return QVariant("1");
}

int PictureModel::_index( const QModelIndex &index )const
{
	const int nIndex = index.row() * columnCount(index) + index.column();
	return nIndex;
}

bool PictureModel::_indexValid( const QModelIndex &index ) const
{
	if (index.isValid() && _index(index)  < _ListModelUnitInfo.size())
	{
		return true;
	}
	return false;
}

int PictureModel::_columeCount() const
{
	if (_pView == NULL || _ListModelUnitInfo.empty() || _pView->width() < COLUME_WIDTH || _pView == NULL)
	{
		return 1;
	}

	const int nViewWidth = _pView->width();
	const int nNum = nViewWidth / COLUME_WIDTH;
	return nNum >= MAX_COLUME_COUNT ? MAX_COLUME_COUNT : nNum;
}

void PictureTableView::slotPressed( const QModelIndex &index )
{
	if(!index.isValid() || !m_pPictureModel)
	{
		return;
	}

	QVariant val = m_pPictureModel->data(index, Qt::UserRole);
	QByteArray arr = val.toByteArray();
	if (arr.isEmpty())
	{
		return;
	}

	QDataStream stream(&arr, QIODevice::ReadOnly);
	ModelUnitInfo info;
	stream.setVersion(QDataStream::Qt_5_0);
	stream >> info;

	QPixmap pixmap;
	if(!pixmap.load(info.strIcon))
	{
		LOG(WARNING) << "PictureTableView Load File" << val.toString().toLocal8Bit().data() << "Failed!";
		return;
	}

	QMimeData *mimeData = new QMimeData;
	mimeData->setData(g_strPictureMimeType, arr);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setPixmap(pixmap);
	drag->setHotSpot(QPoint(PIC_ICON_SIZE/2, PIC_ICON_SIZE/2));

	if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
	{

	}
}