#include "T04_P95_ShapeDrawable.h"
#include <osgdb/ReadFile>
#include <osgdb/WriteFile>
#include <osg/ShapeDrawable>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T04_P95_ShapeDrawable, P95_ShapeDrawable)
T04_P95_ShapeDrawable::T04_P95_ShapeDrawable()
{
    
}

T04_P95_ShapeDrawable::~T04_P95_ShapeDrawable()
{
    
}

osg::Node* T04_P95_ShapeDrawable::getNode()
{
    osg::ref_ptr<osg::Group> root = new osg::Group();

	//设置半径和高度
	float radius = 0.8f;
	float height = 1.0f;

	//创建精细度对象，精细度越高，细分就越多
	osg::ref_ptr<osg::TessellationHints> hints = 
		new osg::TessellationHints;
	//设置精细度为0.5f
	hints->setDetailRatio(0.8f);

	//创建一个叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	//添加一个球体，第一个参数是预定义几何体对象，第二个是精细度，默认为0
	geode->addDrawable(new osg::ShapeDrawable(
		new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f), radius), hints));

	//添加一个正方体
	geode->addDrawable(new osg::ShapeDrawable(
		new osg::Box(osg::Vec3(2.0f,0.0f,0.0f),2*radius), hints));

	//添加一个圆锥
	geode->addDrawable(new osg::ShapeDrawable(
		new osg::Cone(osg::Vec3(4.0f,0.0f,0.0f),radius,height), hints));

	//添加一个圆柱体
	geode->addDrawable(new osg::ShapeDrawable(
		new osg::Cylinder(osg::Vec3(6.0f,0.0f,0.0f),radius,height), hints));

	//添加一个太空舱
	geode->addDrawable(new osg::ShapeDrawable(
		new osg::Capsule(osg::Vec3(8.0f,0.0f,0.0f),radius,height), hints));

    //添加到场景
    root->addChild(geode);

    return root.release();
}
