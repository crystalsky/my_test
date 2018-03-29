/****************************************************************************
**
** Copyright (C) 2005-2014 Vire. All rights reserved.
**
** Vire reserves all rights not expressly granted herein.
**
** VREM 
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
-----------------------------------------------------------------------------
**	创建时间:	15:8:2014	
**	文件名称:	ColorMgr h
**	作	  者:	伏光宝
**  
****************************************************************************/

#ifndef ColorMgr_h__
#define ColorMgr_h__

#include <osg/Vec4>

class ColorMgr
{
public:
	static ColorMgr* getInstance();

	void setColorNum(int val);

	void setMinAndMaxValue(double minValue,double maxValue);
	double min();
	double max();

	osg::Vec4 getColorByValue(double val);
	
protected:
	ColorMgr();
	~ColorMgr();

private:
	int _num;
	double _maxValue;
	double _minValue;
	double _deltaValue;
	static ColorMgr* sIns;
};

#endif // ColorMgr_h__

