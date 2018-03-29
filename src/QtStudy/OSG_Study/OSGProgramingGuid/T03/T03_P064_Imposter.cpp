#include "T03_P064_Imposter.h"
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgSim/Impostor>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T03_P064_Imposter, P064_Imposter)
T03_P064_Imposter::T03_P064_Imposter()
{
	
}

T03_P064_Imposter::~T03_P064_Imposter()
{
	
}

osg::Node* T03_P064_Imposter::getNode()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//����һ���ڵ�,��ȡţ��ģ��
	osg::ref_ptr<osg::Node> node =osgDB::readNodeFile("cow.osg");

	//����һ������ڵ�
	osg::ref_ptr<osgSim::Impostor> impostor = new osgSim::Impostor();
	//����50.0f�Ժ�ʼʹ����ͼ
	impostor->setImpostorThreshold(100.0f);
	//����ģ�͵���ʾ�ķ�Χ��0-10000��
	impostor->addChild(node.get(),0,10000.0f);

	//��ӵ�����
	root->addChild(impostor.get());

	return root.release();
}

