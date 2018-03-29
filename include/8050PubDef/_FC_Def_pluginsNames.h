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
 * @file     : _FC_Def_pluginsNames.h
 * @brief    : 插件名称定义
 * @note     : 
 * @author   : dell
 * @date     : 2014/09/18
 * @version  : 1.0.0.0
 * @CopyRight: 
 *************************************************************************/
#ifndef _FC_Def_pluginsNames_h__
#define _FC_Def_pluginsNames_h__

#include <string>

namespace FacilitiesCommunication
{
	const static std::string g_strPluginName_CenterMediator="中心交互插件";

	const static std::string g_strPluginName_DataStorage="数据存储插件";

	const static std::string g_strPluginName_MapDisplay="态势处理与显示插件";

	const static std::string g_strPluginName_PlanTemplateManagementAndDeploy="预案管理配置与下达插件";

	const static std::string g_strPluginName_FacilitiesManagement="通信手段管理调度插件";

	const static std::string g_strPluginName_EffectEvaluation="通信效能评估插件";

	const static std::string g_strPluginName_FCCenterMain = "FacilityCommunicationMain";
}

#endif // _FC_Def_pluginsNames_h__