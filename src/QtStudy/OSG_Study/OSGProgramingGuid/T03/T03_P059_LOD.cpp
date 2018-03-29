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

	//创建一个节点，读取一个牛的模型
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");

	//创建一个节点，读取滑翔机模型
	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg");

	//创建一个细节层次LOD节点
	osg::ref_ptr<osg::LOD> lode = new osg::LOD();
	//添加子节点，在0-30范围内显示牛
	lode->addChild(node1.get(),0.0f,30.0f);
	//添加子节点，在30-100范围内显示滑翔机
	lode->addChild(node2.get(),30.0f,100.0f);

	//写入lode.osg文件
	osgDB::writeNodeFile(*(lode.get()),"lode.osg");

	//添加到场景
	root->addChild(lode.get());

	return root.release();
}

