/**********************************************************
*Write by FlySky
*zzuxp@163.com  http://www.OsgChina.org   
**********************************************************/

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>

#include <osgUtil/Optimizer>
#include <osgUtil/DelaunayTriangulator>

#include "Tex.h"

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	//����鿴�ڶ����֮���л����Բ鿴������
	viewer->addEventHandler( new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()) );

	osg::ref_ptr<osg::Group> root = new osg::Group();

	//������������
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();

	//���㶥������Ĵ�С
	unsigned int n = sizeof(vertex)/sizeof(float[3]);

	//��Ӷ�������
	for( unsigned int i = 0; i < n; i++ )
	{
		coords->push_back( osg::Vec3(vertex[i][0], vertex[i][1], vertex[i][2] ));
	}

	//����Delaunay����������
	osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator(coords.get());
	//����������
	dt->triangulate();

	//����������
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	//���ö�������
	geometry->setVertexArray(coords.get());

	//���뵽��ͼ��Ԫ
	geometry->addPrimitiveSet(dt->getTriangles());

	//��ӵ�Ҷ�ڵ�
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable( geometry.get());

	root->addChild(geode.get()) ;

	//�Ż���������
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root.get()) ;

	viewer->setSceneData(root.get());

	viewer->realize();

	viewer->run();

	return 0 ;
}