#ifndef PicToolDef_h__
#define PicToolDef_h__

#include <QMap>
#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QRect>
#include <QVector>
#include <QList>

typedef enum emPicModelType
{
	PMT_WarAirPlane,	//战斗机
	PMT_EarlyWaringAirPlane,	//预警机
	PMT_Sattlite,	//卫星
	PMT_Router,	//路由器
	PMT_Server,		//服务器
	PMT_SubNet,		//子网
	PMT_Destroyer,	//驱逐舰
	PMT_AircraftCarrier,	//航母
	PMT_StarStation,	//星关站
	PMT_Terminal,		//终端
}PicModelType;

typedef struct stInnerTypeInfo
{
	stInnerTypeInfo()
	{
		nType = 0;
	}
	int		nType;
	QString strTypeName;
}InnerTypeInfo;

typedef struct stModelUnitInfo
{
	/////////////////////////
	//结构体变量
	QString		strID;
	QString		strIcon;		//2d图片
	QString		strModel;		//3d模型
	QString		strToolTip;		//提示信息
	QString		strName;		//名称
	InnerTypeInfo innerInfo;
	/////////////////////////
	stModelUnitInfo()
	{
		init();
	}

	~stModelUnitInfo()
	{
		release();
	}

	stModelUnitInfo(const stModelUnitInfo& src)
	{
		init();
		*this = src;
	}

	stModelUnitInfo& operator=(const stModelUnitInfo& src)
	{
		if(this != &src)
		{
			release();

			//赋值
			strIcon = src.strIcon;
			strModel = src.strModel;
			strToolTip = src.strToolTip;
			strName = src.strName;
			innerInfo = src.innerInfo;
		}
		return *this;
	}

	//初始化
	void init()
	{
		//赋值

	}

	//析构
	void release()
	{

	}
}ModelUnitInfo;


typedef QList<ModelUnitInfo> ListModelUnitInfo;

typedef struct stTypeModelListInfo
{
	/////////////////////////
	//结构体变量
	ListModelUnitInfo	_listModelUnit;
	InnerTypeInfo		_innerStruct;
	/////////////////////////
	stTypeModelListInfo()
	{
		init();
	}
	
	~stTypeModelListInfo()
	{
		release();
	}
	
	stTypeModelListInfo(const stTypeModelListInfo& src)
	{
		init();
		*this = src;
	}

	stTypeModelListInfo& operator=(const stTypeModelListInfo& src)
	{
		if(this != &src)
		{
			release();
			
			//赋值
			_listModelUnit = src._listModelUnit;
			_innerStruct = src._innerStruct;
		}
		return *this;
	}

	//初始化
	void init()
	{
		//赋值
		
	}

	//析构
	void release()
	{

	}
}TypeModelListInfo;

typedef QList<TypeModelListInfo> ListTypeModelListInfo;

#include <QApplication>
namespace DirPaths
{
	/******************************************************************
	*函数名称: GetAppRootDataPath
	*函数功能: 获取应用程序Data目录
	*参数说明:
	*@return: QString
	*******************************************************************/
	static QString GetAppRootDataPath()
	{
		const QString strData= QApplication::applicationDirPath() + "/" + "../../data";
		return strData;
	}

	/******************************************************************
	*函数名称: GetAppConfPath
	*函数功能: 获取应用程序Data/conf目录
	*参数说明:
	*@return: QString
	*******************************************************************/
	static QString GetAppConfPath()
	{
		const QString strData= GetAppRootDataPath() + "/" + "conf";
		return strData;
	}

	/******************************************************************
	*函数名称: GetAppImagePath
	*函数功能: 获取应用程序Data/image目录
	*参数说明:
	*@return: QString
	*******************************************************************/
	static QString GetAppImagePath()
	{
		const QString strData = GetAppRootDataPath() + "/" + "image";
		return strData;
	}

	/******************************************************************
	*函数名称: GetVRContextPath
	*函数功能: 获取应用程序Data/VR-context目录
	*参数说明:
	*@return: QString
	*******************************************************************/
	static QString GetVRContextPath()
	{
		const QString strData = GetAppRootDataPath() + "/" + "VR-context";
		return strData;
	}

	/******************************************************************
	*函数名称: GetStaticMeshesPath
	*函数功能: 获取应用程序Data/VR-context/StaticMeshes目录
	*参数说明:
	*@return: QString
	*******************************************************************/
	static QString GetStaticMeshesPath()
	{
		const QString strData = GetVRContextPath() + "/" + "StaticMeshes";
		return strData;
	}

	/******************************************************************
	*函数名称: GetStaticTexturesPath
	*函数功能: 获取应用程序Data/VR-context/Textures目录
	*参数说明:
	*@return: QString
	*******************************************************************/
	static QString GetStaticTexturesPath()
	{
		const QString strData = GetVRContextPath() + "/" + "Textures";
		return strData;
	}
}
#endif // PicToolDef_h__
