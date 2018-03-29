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
 * @file     : _FC_Def_ConstChar.h
 * @brief    : 常量字符定义
 * @note     : 
 * @author   : dell
 * @date     : 2014/09/18
 * @version  : 1.0.0.0
 * @CopyRight: 
 *************************************************************************/
#ifndef _FC_Def_ConstChar_h__
#define _FC_Def_ConstChar_h__

#include <QString>

namespace FacilitiesCommunication
{
	const static QString g_strFacilityName1 = QString::fromLocal8Bit("通信手段1");

	const static QString g_strFacilityName2 = QString::fromLocal8Bit("通信手段2");

	const static QString g_strFacilityName3 = QString::fromLocal8Bit("通信手段3");

	const static QString g_strFacilityName4 = QString::fromLocal8Bit("通信手段4");

	//动态UI配置项属性间的分隔符
	const static QString g_strFacilityXMLPropertySlipterChar = ",";

	const static QString g_strDateTimeFormat = "yyyyMMddhhmmsszzz";

	const static QString g_strPeriodTimeFormat = "hhmmss";
}
#endif // _FC_Def_ConstChar_h__
