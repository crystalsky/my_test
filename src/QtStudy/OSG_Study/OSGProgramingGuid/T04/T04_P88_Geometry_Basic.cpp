#include "T04_P88_Geometry_Basic.h"
#include <osg/Geode>
#include <osg/Group>
#include <osgdb/ReadFile>
#include <osgdb/WriteFile>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T04_P88_Geometry_Basic, P88_Geometry_Basic)
T04_P88_Geometry_Basic::T04_P88_Geometry_Basic()
{
	
}

T04_P88_Geometry_Basic::~T04_P88_Geometry_Basic()
{
	
}



osg::ref_ptr<osg::Node> createQuad1()
{
	//创建一个叶节点对象
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	//创建一个几何体对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//创建顶点数组，注意顶点的添加顺序是逆时针的
	osg::ref_ptr<osg::Vec3Array> v= new osg::Vec3Array();
	//添加数据
	v->push_back(osg::Vec3(0.0f,0.0f,0.0f));
	v->push_back(osg::Vec3(1.0f,0.0f,0.0f));
	v->push_back(osg::Vec3(1.0f,0.0f,1.0f));
	v->push_back(osg::Vec3(0.0f,0.0f,1.0f));

	//设置顶点数据
	geom->setVertexArray(v.get());

	//创建纹理坐标
	osg::ref_ptr<osg::Vec2Array> vt= new osg::Vec2Array();
	//添加数据
	vt->push_back(osg::Vec2(0.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,1.0f));
	vt->push_back(osg::Vec2(0.0f,1.0f));

	//设置纹理坐标
	geom->setTexCoordArray(0,vt.get());

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	//添加数据
	vc->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
	vc->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
	vc->push_back(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
	vc->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f));

	//设置颜色数组
	geom->setColorArray(vc.get());
	//设置颜色的绑定方式为单个顶点
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//创建法线数组
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	//添加法线
	nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

	//设置法线数组
	geom->setNormalArray(nc.get());
	//设置法线的绑定方式为全部顶点
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	//添加图元，绘图基元为四边形
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	//添加到叶节点
	geode->addDrawable(geom.get());

	return geode.get();
}

osg::Node* T04_P88_Geometry_Basic::getNode()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//添加到场景
	root->addChild(createQuad1());

	return root.release();
}



