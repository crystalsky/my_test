
#include <osg/Geode>
#include <osg/Group>
#include <osg/Notify>
#include <osg/BlendEquation>

#include <osgDB/Registry>
#include <osgDB/ReadFile>

#include <osgUtil/Optimizer>

#include <osgViewer/Viewer>

#include <iostream>

osg::ref_ptr<osg::Node> createQuad()
{
	//叶结点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	//几何体
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//顶点数组
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0, 0, 0));
	v->push_back(osg::Vec3(1, 0, 0));
	v->push_back(osg::Vec3(1, 0, 1));
	v->push_back(osg::Vec3(0, 0, 1));
	geom->setVertexArray(v);

	//创建纹理坐标
	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;
	vt->push_back(osg::Vec2(0, 0));
	vt->push_back(osg::Vec2(1, 0));
	vt->push_back(osg::Vec2(1, 1));
	vt->push_back(osg::Vec2(0, 1));
	geom->setTexCoordArray(0, vt);

	//设置颜色数组
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array;
	vc->push_back(osg::Vec4(1, 0, 0, 1));
	vc->push_back(osg::Vec4(0, 1, 0, 1));
	vc->push_back(osg::Vec4(0, 0, 1, 1));
	vc->push_back(osg::Vec4(1, 1, 0, 0));
	geom->setColorArray(vc);
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);//绑定单个顶点

	//法线(光照方向)
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array;
	nc->push_back(osg::Vec3(-0.707, -0.707, 0));
	nc->push_back(osg::Vec3(0.707, -0.707, 0));
	nc->push_back(osg::Vec3(0.707, -0.707, 0));
	nc->push_back(osg::Vec3(-0.707, -0.707, 0));
	geom->setNormalArray(nc);
	geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);//全部顶点绑定

	//
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	geode->addDrawable(geom.get());

	return geode;
}

int main( int argc, char **argv )
{
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;    
	
	root->addChild(createQuad());

	osgUtil::Optimizer opt;
	opt.optimize(root);

	viewer.setSceneData( root );

	return viewer.run();
}
