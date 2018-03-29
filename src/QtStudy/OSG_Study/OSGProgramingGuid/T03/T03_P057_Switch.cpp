#include "T03_P057_Switch.h"
#include <osg/Geode>
#include <osg/Group>
#include <osg/Switch>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>
#include "osg/MatrixTransform"
#include "osg/Matrixd"

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T03_P057_Switch, P057_Switch)
T03_P057_Switch::T03_P057_Switch()
{
	
}

T03_P057_Switch::~T03_P057_Switch()
{
	
}

osg::Node* T03_P057_Switch::getNode()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//创建一个节点,读取牛的模型
	osg::ref_ptr<osg::Node> node1 = new osg::Node();
	node1 = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr<osg::MatrixTransform> mxGlider = new osg::MatrixTransform;
	mxGlider->addChild(node1);
	osg::Matrix mx;
	mx.makeTranslate(osg::Vec3d(10.0f, 1.0f, 0));
	mx.rotate(45.9, osg::Vec3f(1, 0, 1.0));
	mxGlider->setMatrix(mx);

	//创建一个节点，读取滑翔机模型
	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg") ;

	//创建一个开关节点，只渲染滑翔机而不渲染牛
	osg::ref_ptr<osg::Switch> swtich =  new osg::Switch();
	//添加牛的模型，但不渲染，默认为true
	swtich->addChild(mxGlider.get(),true);
	//添加滑翔机模型，状态为渲染
	swtich->addChild(node2.get(),true);

	root->addChild(swtich.get());

	return root.release();
}

