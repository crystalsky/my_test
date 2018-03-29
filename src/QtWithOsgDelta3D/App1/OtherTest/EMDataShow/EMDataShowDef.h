#ifndef EMDataShowDef_h__
#define EMDataShowDef_h__

#include <QString>
#include <QDateTime>
#include <QList>
#include <QApplication>
#include "osg\Array"
#include "osg\ref_ptr"
#include <QDebug>

#define CHECK_DOUBLE_EQUAL(a,b) (abs(a - b) < 0.00000001)
#define INVALIDE_MAX_VALUE 9999
#define INVALIDE_MIN_VALUE -9999
namespace EMShowDef
{
	static const QString CALC_RESULT_TIME_TICK_FORMAT = QString::fromLocal8Bit("yyyyMMddhhmmsszzz");
	static const QString LIST_TIME_TICK_FORMAT = QString::fromLocal8Bit("yyyy-MM-dd hh:mm:ss");
	typedef struct stEMDataFileInfo
	{
		/////////////////////////
		//�ṹ�����
		QDateTime	_dateTime;		//�ļ�ʱ��
		QString		_strFileName;	//�ļ���
		QString		_strFileFullPath;	// �ļ�·��
		double		_dHeight;			//�߶�
		double		_dFrequency;		//Ƶ��
		int			_nDataType;		//��������

		void*		_userData;		//�û�ָ��
		/////////////////////////
		stEMDataFileInfo()
		{
			init();
		}

		~stEMDataFileInfo()
		{
			release();
		}

		stEMDataFileInfo(const stEMDataFileInfo& src)
		{
			init();
			*this = src;
		}

		stEMDataFileInfo& operator=(const stEMDataFileInfo& src)
		{
			if(this != &src)
			{
				release();

				//��ֵ
				_dateTime	= src._dateTime;	
				_strFileName = src._strFileName;
				_strFileFullPath = src._strFileFullPath;
				_dHeight = src._dHeight;
				_dFrequency = src._dFrequency;
				_nDataType = src._nDataType;

				_userData = src._userData;	//���ڱ���ָ��ָ��
			}
			return *this;
		}

		inline bool operator==(const stEMDataFileInfo& other)const
		{
			return getID() == other.getID();
		}

		inline bool operator < (const stEMDataFileInfo& other)const
		{
			return dataTimeString() < other.dataTimeString();
		}

		inline QString dataTimeString()const
		{
			return _dateTime.toString(CALC_RESULT_TIME_TICK_FORMAT);
		}

		inline QString getID()const
		{
			return dataTimeString() + _strFileName;
		}

		inline bool checkEqualFreq(double dFreq)const
		{
			return CHECK_DOUBLE_EQUAL(dFreq, this->_dFrequency);
		}

		inline bool checkEqualHeight(double dHei)const
		{
			return CHECK_DOUBLE_EQUAL(dHei, this->_dHeight);
		}

		inline bool checkEqualDataType(double nDataType)const
		{
			return CHECK_DOUBLE_EQUAL(nDataType, this->_nDataType);
		}

		inline bool valid()const
		{
			return !getID().isEmpty();
		}

		//��ʼ��
		void init()
		{
			//��ֵ
			_dHeight = 0;
			_dFrequency = 0;
			_nDataType = 0;
			_userData = 0;
		}

		//����
		void release()
		{

		}
	}EMDataFileInfo;
	typedef QList<EMDataFileInfo> ListEMDataFileInfo;

	//���ε�Ÿ������ݽṹ
	typedef struct stcoverageResultData
	{
		/////////////////////////
		//�ṹ�����
		
		/////////////////////////
		stcoverageResultData()
		{
			init();
		}
		
		~stcoverageResultData()
		{
			release();
		}
		
		stcoverageResultData(const stcoverageResultData& src)
		{
			init();
			*this = src;
		}
	
		stcoverageResultData& operator=(const stcoverageResultData& src)
		{
			if(this != &src)
			{
				release();
				
				//��ֵ
				m_lon	= src.m_lon;
				m_lat	= src.m_lat;
				m_heigh	= src.m_heigh;
				m_maxValue	= src.m_maxValue;
				m_minValue	= src.m_minValue;
				m_row	= src.m_row;
				m_column	= src.m_column;
				m_ratio	= src.m_ratio;

				if (src.m_data != NULL && src.m_row && src.m_column)
				{
					m_data = new double[src.m_row * src.m_column];
					memcpy(m_data, src.m_data, sizeof(double) * src.m_row * src.m_column);
				}
			}
			return *this;
		}
	
		//��ʼ��
		void init()
		{
			//��ֵ
			m_lon	= -180.0;
			m_lat	= -90.0;
			m_heigh	= 0;
			m_maxValue	= 0;
			m_minValue	= 0;
			m_row	= 0;
			m_column	= 0;
			m_ratio	= 1;
			m_data 	= NULL;
		}
	
		//����
		void release()
		{
			if (m_data != NULL)
			{
				delete[] m_data;
				m_data = NULL;
			}
		}

		double m_lon;
		double m_lat;
		double m_heigh;
		double m_maxValue;
		double m_minValue;
		int m_row;
		int m_column;
		double m_ratio;	
		double* m_data;
	}coverageResultData;

	typedef struct stFolderFilesProperty
	{
		QString strFolderName;
		QString strFolderFullPath;
		ListEMDataFileInfo listResultFilesPro;

		EMDataFileInfo getEMDataByHeight(double dHeight)const
		{
			EMDataFileInfo ret;
			for (int i = 0; i < listResultFilesPro.size(); ++i)
			{
				EMDataFileInfo info = listResultFilesPro.at(i);
				if (CHECK_DOUBLE_EQUAL(dHeight, info._dHeight))
				{
					ret = info;
					break;
				}
			}

			return ret;
		}
	}FolderFilesProperty;
	typedef QMap<QDateTime, FolderFilesProperty>	MapDateTimeFolderFilesProperty;
	typedef MapDateTimeFolderFilesProperty::const_iterator IterDateTimeFolderFilesProperty;

	namespace DirPaths
	{
		/******************************************************************
		 *��������: GetAppRootDataPath
		 *��������: ��ȡӦ�ó���Data·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString GetAppRootDataPath()
		{
			const QString strData= QApplication::applicationDirPath() + "/" + "../data";
			return strData;
		}

		/******************************************************************
		 *��������: GetVRContextPath
		 *��������: ��ȡӦ�ó���Data/VR-context·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString GetVRContextPath()
		{
			const QString strData= GetAppRootDataPath() + "/" + "VR-context";
			return strData;
		}

		/******************************************************************
		 *��������: GetStaticMeshesPath
		 *��������: ��ȡӦ�ó���Data/VR-context/StaticMeshes·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString GetStaticMeshesPath()
		{
			const QString strData= GetVRContextPath() + "/" + "StaticMeshes";
			return strData;
		}

		/******************************************************************
		 *��������: GetCfgPath
		 *��������: ��ȡӦ�ó���Data/conf·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString GetCfgPath()
		{
			const QString strCfgPath = GetAppRootDataPath() + "/" + "conf";
			return strCfgPath;
		}
	}

	namespace FilePath
	{
		/******************************************************************
		 *��������: getSettingFilePath
		 *��������: ��ȡӦ�ó���Data/conf/Settings.ini·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString getSettingFilePath()
		{
			return DirPaths::GetCfgPath() + "/" + "Settings.ini";
		}

		/******************************************************************
		 *��������: getNodeSettingFilePath
		 *��������: ��ȡӦ�ó���Data/conf/nodeSetting.ini·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString getNodeSettingFilePath()
		{
			return DirPaths::GetCfgPath() + "/" + "nodeSetting.ini";
		}
		
		/******************************************************************
		 *��������: getNodeSettingFilePath
		 *��������: ��ȡӦ�ó���Data/conf/nodeSetting.ini·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString getMapNameSettingFilePath()
		{
			return DirPaths::GetCfgPath() + "/" + "mapName.ini";
		}

		/******************************************************************
		 *��������: getStatisticsSettingsFilePath
		 *��������: ��ȡӦ�ó���Data/conf/StatisticsSettings.ini·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString getStatisticsSettingsFilePath()
		{
			return DirPaths::GetCfgPath() + "/" + "StatisticsSettings.ini";
		}

		/******************************************************************
		 *��������: getActorModelFreqCfgFilePath
		 *��������: ��ȡӦ�ó���Data/conf/ActorModelFreqCfg.xml·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString getActorModelFreqCfgFilePath()
		{
			return DirPaths::GetCfgPath() + "/" + "ActorModelFreqCfg.xml";
		}

		/******************************************************************
		 *��������: getShortcutCfgFilePath
		 *��������: ��ȡӦ�ó���Data/conf/shortcut.ini·��
		 *����˵��:
		 *@return: QString
		 *******************************************************************/
		static QString getShortcutCfgFilePath()
		{
			return DirPaths::GetCfgPath() + "/" + "shortcut.ini";
		}
	}

	typedef struct stEMDataInfo
	{
		/////////////////////////
		//�ṹ�����
		EMDataFileInfo					_fileInfo;
		osg::ref_ptr<osg::Vec3Array>	_arrVertex3D;
		osg::ref_ptr<osg::Vec3Array>	_arrVertex2D;
		osg::ref_ptr<osg::Vec4Array>	_arrColor;
		double							_dMaxVal;	//ÿ�ļ������ֵ
		double							_dMinVal;	//ÿ�ļ�����Сֵ
		/////////////////////////
		stEMDataInfo()
		{
			qDebug() << "xxxxx....";
			init();
		}
		
		~stEMDataInfo()
		{
			qDebug() << "yyyy....";
			release();
		}
		
		stEMDataInfo(const stEMDataInfo& src)
		{
			init();
			*this = src;
		}
	
		stEMDataInfo& operator=(const stEMDataInfo& src)
		{
			if(this != &src)
			{
				release();
				
				//��ֵ
				_fileInfo = src._fileInfo;
				_arrVertex3D = new osg::Vec3Array(*src._arrVertex3D);
				_arrVertex2D = new osg::Vec3Array(*src._arrVertex2D);
				_arrColor = new osg::Vec4Array(*src._arrColor);
				_dMaxVal = src._dMaxVal;
				_dMinVal = src._dMaxVal;
			}
			return *this;
		}

		inline bool valid()const
		{
			if (!_arrVertex3D.valid() || !_arrColor.valid())
			{
				return false;
			}
			return !_arrVertex3D->empty() && !_arrColor->empty();
		}
	
		//��ʼ��
		void init()
		{
			//��ֵ
			//_arrVertex3D = new osg::Vec3Array;
			//_arrVertex2D = new osg::Vec3Array;
			//_arrColor = new osg::Vec4Array;

			_dMaxVal = INVALIDE_MIN_VALUE;
			_dMinVal = INVALIDE_MAX_VALUE;
		}
	
		//����
		void release()
		{
			/*if (_arrVertex3D.valid())
			{
				_arrVertex3D->clear();
				_arrVertex3D.release();
			}

			if (_arrVertex2D.valid())
			{
				_arrVertex2D->clear();
				_arrVertex2D.release();
			}

			if (_arrColor.valid())
			{
				_arrColor->clear();
				_arrColor.release();
			}*/
		}
	}EMDataInfo;

	typedef QMap<QString, QSharedPointer<EMDataInfo>>	MapCachedEMData;
	typedef QMultiMap<QDateTime, QString>	MapCachedDataInfo;
}



#endif // EMDataShowDef_h__
