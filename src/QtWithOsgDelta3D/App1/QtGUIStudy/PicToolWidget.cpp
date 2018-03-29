#include "glog.h"
#include "PictureTableView.h"
#include "PicToolWidget.h"

PicToolWidget::PicToolWidget(QWidget* pParnet)
	: QWidget(pParnet)
{
	_init();

	_readData();

	_refreshPicToolBox();
}

PicToolWidget::~PicToolWidget()
{

}

void PicToolWidget::_init()
{
	QVBoxLayout* play = new QVBoxLayout(this);
	m_pPicToolBox = new QToolBox(this);
	play->addWidget(m_pPicToolBox);
}

void PicToolWidget::_readData()
{
	m_listAllPicModelInfo.clear();

	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_WarAirPlane;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("ս����");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf1.png";
			info.innerInfo = Typeinfo._innerStruct;
			info.strName = QString("%1%2").arg(QStringLiteral("ս����")).arg(i + 1);
			Typeinfo._listModelUnit << info;
		}

		m_listAllPicModelInfo << Typeinfo;
	}
	
	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_Sattlite;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("����");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf2.png";
			info.innerInfo = Typeinfo._innerStruct;
			info.strName = QString("%1%2").arg(QStringLiteral("����")).arg(i + 1);
			Typeinfo._listModelUnit << info;
		}
		m_listAllPicModelInfo << Typeinfo;

	}

	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_Router;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("·����");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf3.png";
			info.strName = QString("%1%2").arg(QStringLiteral("·����")).arg(i + 1);
			info.innerInfo = Typeinfo._innerStruct;
			Typeinfo._listModelUnit << info;
		}
		m_listAllPicModelInfo << Typeinfo;

	}

	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_Server;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("������");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf4.png";
			info.innerInfo = Typeinfo._innerStruct;
			info.strName = QString("%1%2").arg(QStringLiteral("������")).arg(i + 1);
			Typeinfo._listModelUnit << info;
		}
		m_listAllPicModelInfo << Typeinfo;

	}

	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_EarlyWaringAirPlane;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("Ԥ����");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf4.png";
			info.strName = QString("%1%2").arg(QStringLiteral("Ԥ����")).arg(i + 1);
			info.innerInfo = Typeinfo._innerStruct;
			Typeinfo._listModelUnit << info;
		}
		m_listAllPicModelInfo << Typeinfo;

	}

	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_SubNet;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("����");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf4.png";
			info.strName = QString("%1%2").arg(QStringLiteral("����")).arg(i + 1);
			info.innerInfo = Typeinfo._innerStruct;
			Typeinfo._listModelUnit << info;
		}
		m_listAllPicModelInfo << Typeinfo;

	}

	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_Server;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("������");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf4.png";
			info.strName = QString("%1%2").arg(QStringLiteral("������")).arg(i + 1);
			info.innerInfo = Typeinfo._innerStruct;
			Typeinfo._listModelUnit << info;
		}
		m_listAllPicModelInfo << Typeinfo;

	}

	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_Destroyer;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("����");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf4.png";
			info.strName = QString("%1%2").arg(QStringLiteral("����")).arg(i + 1);
			info.innerInfo = Typeinfo._innerStruct;
			Typeinfo._listModelUnit << info;
		}
		m_listAllPicModelInfo << Typeinfo;

	}

	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_AircraftCarrier;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("��ĸ");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf4.png";
			info.strName = QString("%1%2").arg(QStringLiteral("��ĸ")).arg(i + 1);
			info.innerInfo = Typeinfo._innerStruct;
			Typeinfo._listModelUnit << info;
		}
		m_listAllPicModelInfo << Typeinfo;

	}

	{
		TypeModelListInfo Typeinfo;
		Typeinfo._innerStruct.nType = PMT_StarStation;
		Typeinfo._innerStruct.strTypeName = QStringLiteral("�ǹ�վ");

		for (int i = 0; i < 15; i++)
		{
			ModelUnitInfo info;
			info.strToolTip = QStringLiteral("�ĵĵĵ�");
			info.strIcon = DirPaths::GetAppImagePath() + "/" + "realLeaf4.png";
			info.strName = QString("%1%2").arg(QStringLiteral("�ǹ�վ")).arg(i + 1);
			info.innerInfo = Typeinfo._innerStruct;
			Typeinfo._listModelUnit << info;
		}
		m_listAllPicModelInfo << Typeinfo;

	}

}

void PicToolWidget::_refreshPicToolBox()
{
	for (int i = 0; i < m_listAllPicModelInfo.size(); ++i)
	{
		const TypeModelListInfo& info = m_listAllPicModelInfo.at(i);

		PictureTableView* pView = new PictureTableView(NULL);
		m_pPicToolBox->addItem(pView, info._innerStruct.strTypeName);

		pView->setTypeModelListInfo(info);
	}
}

bool PicToolWidget::eventFilter( QObject *obj, QEvent *event )
{
	if (event->type() == QEvent::DragEnter)
	{
		LOG(INFO) << "QEvent::DragEnter";
	}

	return QObject::eventFilter(obj, event);
}

QSize PicToolWidget::sizeHint() const
{
	return QSize(COLUME_WIDTH * 1.2, 800);
}