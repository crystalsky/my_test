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

	//创建一个节点,读取牛的模型
	osg::ref_ptr<osg::Node> node =osgDB::readNodeFile("cow.osg");

	//创建一个替代节点
	osg::ref_ptr<osgSim::Impostor> impostor = new osgSim::Impostor();
	//设置50.0f以后开始使用贴图
	impostor->setImpostorThreshold(100.0f);
	//设置模型的显示的范围在0-10000内
	impostor->addChild(node.get(),0,10000.0f);

	//添加到场景
	root->addChild(impostor.get());

	return root.release();
}

