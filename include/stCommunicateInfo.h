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
/******************************************************* 
 * @file     : stFacilityCommunicateInfo.h
 * @brief    : 手段通信结构体(用于指定各手段地址和通信端口)
 * @note     : 
 * @author   : dell
 * @date     : 2014/09/11
 * @version  : 1.0.0.0
 * @CopyRight: 
 *******************************************************/

#ifndef stCommunicateInfo_h__
#define stCommunicateInfo_h__

#include <QString>
#include <QMap>

class stCommunicateInfo
{
public:
	stCommunicateInfo(const QString& strFacilityID = "",
		int nLocalPort = 0,
		const QString& strRemoteIP = "",
		int nRemotePort = 0)
	{
		this->strFacilityID = strFacilityID;
		this->strRemoteIP = strRemoteIP;
		this->nLocalPort = nLocalPort;
		this->nRemotePort = nRemotePort;
	}
	QString strFacilityID;
	int nLocalPort;
	QString strRemoteIP;
	int nRemotePort;
};
typedef QMap<QString, stCommunicateInfo> MapFacilityCommunicateInfo;

#endif // stCommunicateInfo_h__