#include "T03_P061_PagedLOD.h"
#include <osg/Geode>
#include <osg/Group>
#include <osg/PagedLOD>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile> 
#include <osgDB/WriteFile>

#include <osgGA/TrackballManipulator>

#include <osgUtil/Optimizer>

#include <iostream>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T03_P061_PagedLOD, P061_PagedLOD)
T03_P061_PagedLOD::T03_P061_PagedLOD()
{
	
}

T03_P061_PagedLOD::~T03_P061_PagedLOD()
{
	
}


//��������PagedLOD����
osg::ref_ptr<osg::Group> createPagedLOD()
{
	//����PagedLOD����
	osg::ref_ptr<osg::PagedLOD> page = new osg::PagedLOD();
	//��������λ��
	page->setCenter(osg::Vec3(0.0f,0.0f,0.0f));

	//��ӽڵ㣬����0��������Ϊcow.osg
	page->setFileName(0,"cow.osg");
	//���ÿ��ӱ仯��ΧΪ0.0f-50.0f
	page->setRange(0,0.0f,50.0f);

	//��ӽڵ㣬����0��������Ϊspaceship.osg
	page->setFileName(1,"glider.osg");
	//���ÿ��ӱ仯��Χ50.0f-100.0f
	page->setRange(1,50.0f,180.0f);

	//��ӽڵ㣬����0��������Ϊcessna.osg
	page->setFileName(2,"cessna.osg");
	//���ÿ��ӱ仯��Χ100.0f-200.0f
	page->setRange(2,100.0f,200.0f);

	return page.get();
}

osg::Node* T03_P061_PagedLOD::getNode()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//��������任�ڵ�
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	//����ӽڵ�
	mt->addChild(createPagedLOD());
	//��תһ�£�����һ�º��ʵĽǶ�
	osg::Matrix m ;
	m.makeRotate(60.0f,0.0f,0.0f,1.0f);
	//���þ���
	mt->setMatrix(m);

	//���PagedLOD����
	root->addChild(mt.get()) ;

	//д��PagedLOD
	osgDB::writeNodeFile(*root,"page.osg");

	return root.release();
}

