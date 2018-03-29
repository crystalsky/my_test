#include "T03_P071_CoordinateSystemNode.h"
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/CoordinateSystemNode>
#include <osg/BoundingBox>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <iostream>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T03_P071_CoordinateSystemNode, P071_CoordinateSystemNode)
T03_P071_CoordinateSystemNode::T03_P071_CoordinateSystemNode()
{
	
}

T03_P071_CoordinateSystemNode::~T03_P071_CoordinateSystemNode()
{
	
}


//����һ������
osg::ref_ptr<osg::Node> createEarth()
{
	//����һ������
	osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0,0.0,0.0), osg::WGS_84_RADIUS_POLAR));

	//��ӵ�Ҷ�ڵ�
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(sd.get());

	//��������
	std::string filename("Images/land_shallow_topo_2048.jpg");
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::Texture2D(osgDB::readImageFile(filename)));

	//��������ϵ�ڵ�
	osg::ref_ptr<osg::CoordinateSystemNode> csn = new osg::CoordinateSystemNode;
	//������Բ��ģ�ͣ�Ĭ�ϵ�����ϵWGS_84
	csn->setEllipsoidModel(new osg::EllipsoidModel());
	//����ӽڵ�
	csn->addChild(geode.get());

	return csn.get();
}


osg::Node* T03_P071_CoordinateSystemNode::getNode()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//����ڵ�����
	root->addChild(createEarth());

	return root.release();
}

