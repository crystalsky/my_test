#include "ColorMgr.h"

#include <osgSim/ColorRange>


ColorMgr* ColorMgr::sIns = 0L;

ColorMgr::ColorMgr():
	_num(10),
	_deltaValue(1.0)
{
}


ColorMgr::~ColorMgr()
{
}

ColorMgr* ColorMgr::getInstance()
{
	if (0L == sIns)
	{
		sIns = new ColorMgr;
	}
	return sIns;
}

void ColorMgr::setColorNum( int val )
{
	if (_num < 1)
	{
		return;
	}
	_num = val;
}

osg::Vec4 ColorMgr::getColorByValue( double val )
{
	//osgSim::ColorRange clrRange(_minValue , _maxValue);
	//return clrRange.getColor(val);
	osgSim::ColorRange clrRange(-(float)(_num),0.0);

	int lastVal = int((val - _minValue)/_deltaValue);
	return clrRange.getColor(-_num+lastVal);
}

void ColorMgr::setMinAndMaxValue( double minValue,double maxValue )
{
	_maxValue = minValue;
	_minValue = maxValue;
	_deltaValue = (_maxValue - _minValue)/float(_num);
}

double ColorMgr::min()
{
	return _minValue;
}

double ColorMgr::max()
{
	return _maxValue;
}
