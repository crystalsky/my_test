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
		//手段调度信息
		typedef struct stFacilityDispatchInfo
		{
			/////////////////////////
			//结构体变量
			Def_Enum::FacilityDispatchType	type;					//执行方式
			QStringList				listFacilityParamID;	//执行方式关联的手段参数ID
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

					//赋值
					type = src.type;
					listFacilityParamID = src.listFacilityParamID;
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
		}FacilityDispatchInfo;
		typedef QVector<FacilityDispatchInfo> ArrayFacilityDispatchInfo;

		//预案基本信息
		typedef struct stPlanInfo
		{
			/////////////////////////
			//结构体变量
			QString		strPlan_ID;					//预案UUID
			QString		strTemplateIdentify;		//预案模板标识
			QString 	strTemplateDesc;			//预案描述
			QString 	strPlanIdentify;			//预案标识
			bool		IsUpdate;					//是否更新
			QString 	strPlanTime;				//预案时间
			QString 	strPlanState;				//预案状态
			QString 	strPlanUseCondition;		//预案适用条件
			QString 	strPlanCapabilityDesc;		//预案能力描述
			QString 	strPlanUpdateTime;			//预案更新时间
			QString		strFacilitiesDispatchParam;	//手段调度参数信息
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

					//赋值
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

			//初始化
			void init()
			{
				//赋值
				IsUpdate  =false;
			}

			//析构
			void release()
			{

			}
		}PlanInfo;

		//动态手段UI信息
		typedef struct stFacilityDynUI
		{
			/////////////////////////
			//结构体变量
			QString 	strFacilityUI_ID;			//动态手段UI模板ID
			QString 	strFacilityName;			//手段名称
			QString 	strFacilityVersion;			//版本信息
			QString 	strSaveTime;				//时间信息
			QByteArray  byteUIXMLData;				//手段UI轻量模板数据
			QString 	strXMLPropertyNames;		//手段UI轻量模板字段信息(必填)
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

					//赋值
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

			//初始化
			void init()
			{
				//赋值

			}

			//析构
			void release()
			{

			}
		}FacilityDynUI;

		//动态UI配置的参数信息
		typedef struct stFacilityParam
		{
			/////////////////////////
			//结构体变量
			QString			strFacilityParam_ID;	//参数ID
			FacilityDynUI	objFacilityUI;			//动态手段UI信息
			QString 		strConfigTime;			//配置时间
			QString			strExcutePeriodTime;	//执行持续时间
			QString			strParamXMLData;		//手段参数据
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

					//赋值
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

			//初始化
			void init()
			{
				//赋值

			}

			//析构
			void release()
			{

			}
		}FacilityParam;
		typedef QVector<FacilityParam> ArrayFacilityParam;
		typedef ArrayFacilityParam::const_iterator IterArrayFacilityParam;

		//预案信息
		typedef struct stPlanFacilityParam
		{
			/////////////////////////
			//结构体变量
			PlanInfo					planBaseInfo;				//预案模板基本信息
			ArrayFacilityParam			arrayParam;					//手段参数信息
			ArrayFacilityDispatchInfo	arrayFacilityDispatchInfo;	//手段调度逻辑信息
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

					//赋值
					planBaseInfo = src.planBaseInfo;
					arrayParam = src.arrayParam;
					arrayFacilityDispatchInfo = src.arrayFacilityDispatchInfo;
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
				arrayParam.clear();
				arrayFacilityDispatchInfo.clear();
			}
		}PlanFacilityParam;
		typedef QVector<PlanFacilityParam>	ArrayPlanFacilityParam;

		//任务信息
		typedef struct stFCTaskInfo
		{
			/////////////////////////
			//结构体变量
			QString		strTaskID;			//任务ID
			QString		strTaskName;		//任务名称
			QString		strStartTime;		//任务开始时间
			QString		strEndTime;			//任务结否时间
			QString		strTaskDescription;	//任务描述
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

					//赋值
					strTaskID = src.strTaskID;
					strTaskName = src.strTaskName;	
					strStartTime = src.strStartTime;	
					strEndTime = src.strEndTime;		
					strTaskDescription = src.strTaskDescription;
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
		}FCTaskInfo;

		//飞机态势数
		typedef struct stPlaneState
		{
			/////////////////////////
			//结构体变量
			QString			strEntityID;		//对象标识
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
					
					//赋值
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
		
			//初始化
			void init()
			{
				//赋值
				dLongitude = 0;
				dLatitude = 0;
				dAltitude = 0;
				dHeading = 0;
				dSpeed = 0;
				nLinkUsing = 0;
			}
		
			//析构
			void release()
			{
		
			}
		}PlaneState;

		//手段1通信态势信息
		typedef struct stFacility1CommuState
		{
			/////////////////////////
			//结构体变量
			
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
					
					//赋值
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
		}Facility1CommuState;

		//手段2通信态势信息
		typedef struct stFacility2CommuState
		{
			/////////////////////////
			//结构体变量
			
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
					
					//赋值
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
		}Facility2CommuState;

		//手段3通信态势信息
		typedef struct stFacility3CommuState
		{
			/////////////////////////
			//结构体变量
			
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
					
					//赋值
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
		}Facility3CommuState;

		//手段4通信态势信息
		typedef struct stFacility4CommuState
		{
			/////////////////////////
			//结构体变量
			
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
					
					//赋值
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
		}Facility4CommuState;

		//手段通信结构体(用于指定各地址和通信端口)
		typedef struct stCommunicateCfg
		{
			/////////////////////////
			//结构体变量
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
					
					//赋值
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
		}CommunicateCfg;
		typedef QMap<QString, CommunicateCfg> MapCommunicateCfg;
	}
}

#endif // _FC_Def_BussinessStruct_h__