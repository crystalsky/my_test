//************************************************************************/
//********************---------------------------------*******************/
//*******************|    Copyright (c) 2003 - 2014    |******************/
//*******************|      by ViRe Technologies.      |******************/
//*******************|       All Rights Reserved       |******************/
//********************---------------------------------*******************/
//************************************************************************/
//
// If any question, please write to VIRE Technologies for 
// more information: 
//			Room 1222,High Tech Mansion of BUPT, 
//			Beijing, China
//			Post Code: 100876.
// 
// For more, please visit company website: www.vi-re.com
//************************************************************************/
/************************************************************************* 
* @file     : _FC_Def_Enum.h
* @brief    : 相关枚举类型定义
* @note     : 
* @author   : dell
* @date     : 2014/09/18
* @version  : 1.0.0.0
* @CopyRight: 
*************************************************************************/
#ifndef _FC_Def_Enum_h__
#define _FC_Def_Enum_h__

namespace FacilitiesCommunication
{
	namespace Def_Enum
	{
		/**
		* 手段调度类型
		*/
		typedef enum emFacilityDispatchType
		{
			FDT_Order,			/**< 顺序方式*/
			FDT_Simultaneity,	/**< 同时方式*/
			FDT_Waiting,		/**< 执守方式*/
		}FacilityDispatchType;

		/**
		* 消息类型
		*/
		typedef enum emLogMsgType
		{
			LMT_Log2File,		/**< 文件日志*/	
			LMT_Log2WidgetShow,	/**< 窗体日志区显示*/
			LMG_Log2MessageBox,	/**< 弹框显示*/
		}LogMsgType;

		/**
		* 消息类型
		*/
		typedef enum emLogMsgLevel
		{
			LML_Success,	/**< 成功*/	
			LML_Warning,	/**< 警告*/
			LML_Error,		/**< 错误*/
		}LogMsgLevel;

		typedef enum emCommunicationDataType
		{
			CDT_Facility1_StateData,		//通信手段1态势数据
			CDT_Facility2_StateData,		//通信手段2态势数据
			CDT_Facility3_StateData,		//通信手段3态势数据
			CDT_Facility4_StateData,		//通信手段4态势数据
		}CommunicationDataType;
	}
}

#endif // _FC_Def_Enum_h__