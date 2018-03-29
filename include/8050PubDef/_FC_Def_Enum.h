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
* @brief    : ���ö�����Ͷ���
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
		* �ֶε�������
		*/
		typedef enum emFacilityDispatchType
		{
			FDT_Order,			/**< ˳��ʽ*/
			FDT_Simultaneity,	/**< ͬʱ��ʽ*/
			FDT_Waiting,		/**< ִ�ط�ʽ*/
		}FacilityDispatchType;

		/**
		* ��Ϣ����
		*/
		typedef enum emLogMsgType
		{
			LMT_Log2File,		/**< �ļ���־*/	
			LMT_Log2WidgetShow,	/**< ������־����ʾ*/
			LMG_Log2MessageBox,	/**< ������ʾ*/
		}LogMsgType;

		/**
		* ��Ϣ����
		*/
		typedef enum emLogMsgLevel
		{
			LML_Success,	/**< �ɹ�*/	
			LML_Warning,	/**< ����*/
			LML_Error,		/**< ����*/
		}LogMsgLevel;

		typedef enum emCommunicationDataType
		{
			CDT_Facility1_StateData,		//ͨ���ֶ�1̬������
			CDT_Facility2_StateData,		//ͨ���ֶ�2̬������
			CDT_Facility3_StateData,		//ͨ���ֶ�3̬������
			CDT_Facility4_StateData,		//ͨ���ֶ�4̬������
		}CommunicationDataType;
	}
}

#endif // _FC_Def_Enum_h__