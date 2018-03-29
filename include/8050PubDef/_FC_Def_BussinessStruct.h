#ifndef _FC_Def_BussinessStruct_h__
#define _FC_Def_BussinessStruct_h__

#include <QString>
#include <QVector>
#include <QStringList>
#include "_FC_Def_ConstChar.h"
#include "_FC_Def_Enum.h"

namespace FacilitiesCommunication
{
	namespace Def_BussinessStruct
	{
		//�ֶε�����Ϣ
		typedef struct stFacilityDispatchInfo
		{
			/////////////////////////
			//�ṹ�����
			Def_Enum::FacilityDispatchType	type;					//ִ�з�ʽ
			QStringList				listFacilityParamID;	//ִ�з�ʽ�������ֶβ���ID
			/////////////////////////
			stFacilityDispatchInfo()
			{
				init();
			}

			~stFacilityDispatchInfo()
			{
				release();
			}

			stFacilityDispatchInfo(const stFacilityDispatchInfo& src)
			{
				init();
				*this = src;
			}

			stFacilityDispatchInfo& operator=(const stFacilityDispatchInfo& src)
			{
				if(this != &src)
				{
					release();

					//��ֵ
					type = src.type;
					listFacilityParamID = src.listFacilityParamID;
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
		}FacilityDispatchInfo;
		typedef QVector<FacilityDispatchInfo> ArrayFacilityDispatchInfo;

		//Ԥ��������Ϣ
		typedef struct stPlanInfo
		{
			/////////////////////////
			//�ṹ�����
			QString		strPlan_ID;					//Ԥ��UUID
			QString		strTemplateIdentify;		//Ԥ��ģ���ʶ
			QString 	strTemplateDesc;			//Ԥ������
			QString 	strPlanIdentify;			//Ԥ����ʶ
			bool		IsUpdate;					//�Ƿ����
			QString 	strPlanTime;				//Ԥ��ʱ��
			QString 	strPlanState;				//Ԥ��״̬
			QString 	strPlanUseCondition;		//Ԥ����������
			QString 	strPlanCapabilityDesc;		//Ԥ����������
			QString 	strPlanUpdateTime;			//Ԥ������ʱ��
			QString		strFacilitiesDispatchParam;	//�ֶε��Ȳ�����Ϣ
			/////////////////////////
			stPlanInfo()
			{
				init();
			}

			~stPlanInfo()
			{
				release();
			}

			stPlanInfo(const stPlanInfo& src)
			{
				*this = src;
			}

			stPlanInfo& operator=(const stPlanInfo& src)
			{
				if(this != &src)
				{
					release();

					//��ֵ
					strPlan_ID = src.strPlan_ID;
					strTemplateIdentify = src.strTemplateIdentify;
					strTemplateDesc = src.strTemplateDesc;
					strPlanIdentify = src.strPlanIdentify;
					IsUpdate = src.IsUpdate;
					strPlanTime = src.strPlanTime;
					strPlanState = src.strPlanState;
					strPlanUseCondition = src.strPlanUseCondition;
					strPlanCapabilityDesc = src.strPlanCapabilityDesc;
					strPlanUpdateTime = src.strPlanUpdateTime;
				}
				return *this;
			}

			//��ʼ��
			void init()
			{
				//��ֵ
				IsUpdate  =false;
			}

			//����
			void release()
			{

			}
		}PlanInfo;

		//��̬�ֶ�UI��Ϣ
		typedef struct stFacilityDynUI
		{
			/////////////////////////
			//�ṹ�����
			QString 	strFacilityUI_ID;			//��̬�ֶ�UIģ��ID
			QString 	strFacilityName;			//�ֶ�����
			QString 	strFacilityVersion;			//�汾��Ϣ
			QString 	strSaveTime;				//ʱ����Ϣ
			QByteArray  byteUIXMLData;				//�ֶ�UI����ģ������
			QString 	strXMLPropertyNames;		//�ֶ�UI����ģ���ֶ���Ϣ(����)
			/////////////////////////
			stFacilityDynUI()
			{
				init();
			}

			~stFacilityDynUI()
			{
				release();
			}

			stFacilityDynUI(const stFacilityDynUI& src)
			{
				*this = src;
			}

			stFacilityDynUI& operator=(const stFacilityDynUI& src)
			{
				if(this != &src)
				{
					release();

					//��ֵ
					strFacilityUI_ID = src.strFacilityUI_ID;
					strFacilityName = src.strFacilityName;
					strFacilityVersion = src.strFacilityVersion;
					strSaveTime = src.strSaveTime;
					byteUIXMLData = src.byteUIXMLData;
					strXMLPropertyNames = src.strXMLPropertyNames;
				}
				return *this;
			}

			QStringList getUIXMLPropertys()const
			{
				return strXMLPropertyNames.split(g_strFacilityXMLPropertySlipterChar);
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
		}FacilityDynUI;

		//��̬UI���õĲ�����Ϣ
		typedef struct stFacilityParam
		{
			/////////////////////////
			//�ṹ�����
			QString			strFacilityParam_ID;	//����ID
			FacilityDynUI	objFacilityUI;			//��̬�ֶ�UI��Ϣ
			QString 		strConfigTime;			//����ʱ��
			QString			strExcutePeriodTime;	//ִ�г���ʱ��
			QString			strParamXMLData;		//�ֶβ�����
			/////////////////////////
			stFacilityParam()
			{
				init();
			}

			~stFacilityParam()
			{
				release();
			}

			stFacilityParam(const stFacilityParam& src)
			{
				init();
				*this = src;
			}

			stFacilityParam& operator=(const stFacilityParam& src)
			{
				if(this != &src)
				{
					release();

					//��ֵ
					strFacilityParam_ID = src.strFacilityParam_ID;
					objFacilityUI = src.objFacilityUI;
					strConfigTime = src.strConfigTime;
					strExcutePeriodTime = src.strExcutePeriodTime;
					strParamXMLData = src.strParamXMLData;
				}
				return *this;
			}

			bool operator==(const QString& strID)const 
			{
				return this->strFacilityParam_ID == strID;
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
		}FacilityParam;
		typedef QVector<FacilityParam> ArrayFacilityParam;
		typedef ArrayFacilityParam::const_iterator IterArrayFacilityParam;

		//Ԥ����Ϣ
		typedef struct stPlanFacilityParam
		{
			/////////////////////////
			//�ṹ�����
			PlanInfo					planBaseInfo;				//Ԥ��ģ�������Ϣ
			ArrayFacilityParam			arrayParam;					//�ֶβ�����Ϣ
			ArrayFacilityDispatchInfo	arrayFacilityDispatchInfo;	//�ֶε����߼���Ϣ
			/////////////////////////
			stPlanFacilityParam()
			{
				init();
			}

			~stPlanFacilityParam()
			{
				release();
			}

			stPlanFacilityParam(const stPlanFacilityParam& src)
			{
				init();
				*this = src;
			}

			stPlanFacilityParam& operator=(const stPlanFacilityParam& src)
			{
				if(this != &src)
				{
					release();

					//��ֵ
					planBaseInfo = src.planBaseInfo;
					arrayParam = src.arrayParam;
					arrayFacilityDispatchInfo = src.arrayFacilityDispatchInfo;
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
				arrayParam.clear();
				arrayFacilityDispatchInfo.clear();
			}
		}PlanFacilityParam;
		typedef QVector<PlanFacilityParam>	ArrayPlanFacilityParam;

		//������Ϣ
		typedef struct stFCTaskInfo
		{
			/////////////////////////
			//�ṹ�����
			QString		strTaskID;			//����ID
			QString		strTaskName;		//��������
			QString		strStartTime;		//����ʼʱ��
			QString		strEndTime;			//������ʱ��
			QString		strTaskDescription;	//��������
			/////////////////////////
			stFCTaskInfo()
			{
				init();
			}

			~stFCTaskInfo()
			{
				release();
			}

			stFCTaskInfo(const stFCTaskInfo& src)
			{
				init();
				*this = src;
			}

			stFCTaskInfo& operator=(const stFCTaskInfo& src)
			{
				if(this != &src)
				{
					release();

					//��ֵ
					strTaskID = src.strTaskID;
					strTaskName = src.strTaskName;	
					strStartTime = src.strStartTime;	
					strEndTime = src.strEndTime;		
					strTaskDescription = src.strTaskDescription;
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
		}FCTaskInfo;

		//�ɻ�̬����
		typedef struct stPlaneState
		{
			/////////////////////////
			//�ṹ�����
			QString			strEntityID;		//�����ʶ
			double			dLongitude;
			double			dLatitude;
			double			dAltitude;
			double			dHeading;
			double			dSpeed;
			int 			nLinkUsing;
			/////////////////////////
			stPlaneState()
			{
				init();
			}
			
			~stPlaneState()
			{
				release();
			}
			
			stPlaneState(const stPlaneState& src)
			{
				init();
				*this = src;
			}
		
			stPlaneState& operator=(const stPlaneState& src)
			{
				if(this != &src)
				{
					release();
					
					//��ֵ
					strEntityID = src.strEntityID;
					dLongitude = src.dLongitude;
					dLatitude = src.dLatitude;
					dAltitude = src.dAltitude;
					dHeading = src.dHeading;
					dSpeed = src.dSpeed;
					nLinkUsing = src.nLinkUsing;
				}
				return *this;
			}
		
			//��ʼ��
			void init()
			{
				//��ֵ
				dLongitude = 0;
				dLatitude = 0;
				dAltitude = 0;
				dHeading = 0;
				dSpeed = 0;
				nLinkUsing = 0;
			}
		
			//����
			void release()
			{
		
			}
		}PlaneState;

		//�ֶ�1ͨ��̬����Ϣ
		typedef struct stFacility1CommuState
		{
			/////////////////////////
			//�ṹ�����
			
			/////////////////////////
			stFacility1CommuState()
			{
				init();
			}
			
			~stFacility1CommuState()
			{
				release();
			}
			
			stFacility1CommuState(const stFacility1CommuState& src)
			{
				init();
				*this = src;
			}
		
			stFacility1CommuState& operator=(const stFacility1CommuState& src)
			{
				if(this != &src)
				{
					release();
					
					//��ֵ
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
		}Facility1CommuState;

		//�ֶ�2ͨ��̬����Ϣ
		typedef struct stFacility2CommuState
		{
			/////////////////////////
			//�ṹ�����
			
			/////////////////////////
			stFacility2CommuState()
			{
				init();
			}
			
			~stFacility2CommuState()
			{
				release();
			}
			
			stFacility2CommuState(const stFacility2CommuState& src)
			{
				init();
				*this = src;
			}
		
			stFacility2CommuState& operator=(const stFacility2CommuState& src)
			{
				if(this != &src)
				{
					release();
					
					//��ֵ
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
		}Facility2CommuState;

		//�ֶ�3ͨ��̬����Ϣ
		typedef struct stFacility3CommuState
		{
			/////////////////////////
			//�ṹ�����
			
			/////////////////////////
			stFacility3CommuState()
			{
				init();
			}
			
			~stFacility3CommuState()
			{
				release();
			}
			
			stFacility3CommuState(const stFacility3CommuState& src)
			{
				init();
				*this = src;
			}
		
			stFacility3CommuState& operator=(const stFacility3CommuState& src)
			{
				if(this != &src)
				{
					release();
					
					//��ֵ
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
		}Facility3CommuState;

		//�ֶ�4ͨ��̬����Ϣ
		typedef struct stFacility4CommuState
		{
			/////////////////////////
			//�ṹ�����
			
			/////////////////////////
			stFacility4CommuState()
			{
				init();
			}
			
			~stFacility4CommuState()
			{
				release();
			}
			
			stFacility4CommuState(const stFacility4CommuState& src)
			{
				init();
				*this = src;
			}
		
			stFacility4CommuState& operator=(const stFacility4CommuState& src)
			{
				if(this != &src)
				{
					release();
					
					//��ֵ
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
		}Facility4CommuState;

		//�ֶ�ͨ�Žṹ��(����ָ������ַ��ͨ�Ŷ˿�)
		typedef struct stCommunicateCfg
		{
			/////////////////////////
			//�ṹ�����
			QString strFacilityID;
			int nLocalPort;
			QString strRemoteIP;
			int nRemotePort;
			/////////////////////////
			stCommunicateCfg(const QString& strFacilityID = "",
				int nLocalPort = 0,
				const QString& strRemoteIP = "",
				int nRemotePort = 0)
			{
				init();
				
				this->strFacilityID = strFacilityID;
				this->strRemoteIP = strRemoteIP;
				this->nLocalPort = nLocalPort;
				this->nRemotePort = nRemotePort;
			}
			
			~stCommunicateCfg()
			{
				release();
			}
			
			stCommunicateCfg(const stCommunicateCfg& src)
			{
				init();
				*this = src;
			}
		
			stCommunicateCfg& operator=(const stCommunicateCfg& src)
			{
				if(this != &src)
				{
					release();
					
					//��ֵ
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
		}CommunicateCfg;
		typedef QMap<QString, CommunicateCfg> MapCommunicateCfg;
	}
}

#endif // _FC_Def_BussinessStruct_h__