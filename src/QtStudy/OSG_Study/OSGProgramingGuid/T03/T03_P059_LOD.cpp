#include "T03_P059_LOD.h"
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/LOD>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T03_P059_LOD, P059_LOD)
T03_P059_LOD::T03_P059_LOD()
{

}

T03_P059_LOD::~T03_P059_LOD()
{

}

osg::Node* T03_P059_LOD::getNode()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//����һ���ڵ㣬��ȡһ��ţ��ģ��
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");

	//����һ���ڵ㣬��ȡ�����ģ��
	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg");

	//����һ��ϸ�ڲ��LOD�ڵ�
	osg::ref_ptr<osg::LOD> lode = new osg::LOD();
	//����ӽڵ㣬��0-30��Χ����ʾţ
	lode->addChild(node1.get(),0.0f,30.0f);
	//����ӽڵ㣬��30-100��Χ����ʾ�����
	lode->addChild(node2.get(),30.0f,100.0f);

	//д��lode.osg�ļ�
	osgDB::writeNodeFile(*(lode.get()),"lode.osg");

	//��ӵ�����
	root->addChild(lode.get());

	return root.release();
}

