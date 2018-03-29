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
	PMT_WarAirPlane,	//ս����
	PMT_EarlyWaringAirPlane,	//Ԥ����
	PMT_Sattlite,	//����
	PMT_Router,	//·����
	PMT_Server,		//������
	PMT_SubNet,		//����
	PMT_Destroyer,	//����
	PMT_AircraftCarrier,	//��ĸ
	PMT_StarStation,	//�ǹ�վ
	PMT_Terminal,		//�ն�
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
	//�ṹ�����
	QString		strID;
	QString		strIcon;		//2dͼƬ
	QString		strModel;		//3dģ��
	QString		strToolTip;		//��ʾ��Ϣ
	QString		strName;		//����
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

			//��ֵ
			strIcon = src.strIcon;
			strModel = src.strModel;
			strToolTip = src.strToolTip;
			strName = src.strName;
			innerInfo = src.innerInfo;
		}
		return *this;
	}

	//��ʼ��
	void init()
	{
		//��ֵ

	}

	//����
	void release()
	{

	}
}ModelUnitInfo;


typedef QList<ModelUnitInfo> ListModelUnitInfo;

typedef struct stTypeModelListInfo
{
	/////////////////////////
	//�ṹ�����
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
			
			//��ֵ
			_listModelUnit = src._listModelUnit;
			_innerStruct = src._innerStruct;
		}
		return *this;
	}

	//��ʼ��
	void init()
	{
		//��ֵ
		
	}

	//����
	void release()
	{

	}
}TypeModelListInfo;

typedef QList<TypeModelListInfo> ListTypeModelListInfo;

#include <QApplication>
namespace DirPaths
{
	/******************************************************************
	*��������: GetAppRootDataPath
	*��������: ��ȡӦ�ó���DataĿ¼
	*����˵��:
	*@return: QString
	*******************************************************************/
	static QString GetAppRootDataPath()
	{
		const QString strData= QApplication::applicationDirPath() + "/" + "../../data";
		return strData;
	}

	/******************************************************************
	*��������: GetAppConfPath
	*��������: ��ȡӦ�ó���Data/confĿ¼
	*����˵��:
	*@return: QString
	*******************************************************************/
	static QString GetAppConfPath()
	{
		const QString strData= GetAppRootDataPath() + "/" + "conf";
		return strData;
	}

	/******************************************************************
	*��������: GetAppImagePath
	*��������: ��ȡӦ�ó���Data/imageĿ¼
	*����˵��:
	*@return: QString
	*******************************************************************/
	static QString GetAppImagePath()
	{
		const QString strData = GetAppRootDataPath() + "/" + "image";
		return strData;
	}

	/******************************************************************
	*��������: GetVRContextPath
	*��������: ��ȡӦ�ó���Data/VR-contextĿ¼
	*����˵��:
	*@return: QString
	*******************************************************************/
	static QString GetVRContextPath()
	{
		const QString strData = GetAppRootDataPath() + "/" + "VR-context";
		return strData;
	}

	/******************************************************************
	*��������: GetStaticMeshesPath
	*��������: ��ȡӦ�ó���Data/VR-context/StaticMeshesĿ¼
	*����˵��:
	*@return: QString
	*******************************************************************/
	static QString GetStaticMeshesPath()
	{
		const QString strData = GetVRContextPath() + "/" + "StaticMeshes";
		return strData;
	}

	/******************************************************************
	*��������: GetStaticTexturesPath
	*��������: ��ȡӦ�ó���Data/VR-context/TexturesĿ¼
	*����˵��:
	*@return: QString
	*******************************************************************/
	static QString GetStaticTexturesPath()
	{
		const QString strData = GetVRContextPath() + "/" + "Textures";
		return strData;
	}
}
#endif // PicToolDef_h__
