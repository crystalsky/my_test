#include "T03_P050_PositionAttitudeTransform.h"
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osg/AutoTransform>

//IMPLEMENT_REFLECTED_CLASS(T03_P050_PositionAttitudeTransform)
IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T03_P050_PositionAttitudeTransform, P050_PositionAttitudeTransform)
T03_P050_PositionAttitudeTransform::T03_P050_PositionAttitudeTransform()
{
	std::string s = getClassName();
}

T03_P050_PositionAttitudeTransform::~T03_P050_PositionAttitudeTransform()
{
	
}

osg::Node* T03_P050_PositionAttitudeTransform::getNode()
{
	//创建场景组节点
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//创建一个节点,读取牛的模型
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	//创建位置变换节点pat1
	osg::ref_ptr<osg::PositionAttitudeTransform> pat1 = new osg::PositionAttitudeTransform() ;
	//设置位置为osg::Vec3(-10.0f,0.0f,0.0f)
	pat1->setPosition(osg::Vec3(10.0f,-5.0f,-2.0f));
	//设置缩放,在X,Y,Z方向都缩小一倍
	pat1->setScale(osg::Vec3(0.3f,0.3f,0.3f));
	//添加子节点
	pat1->addChild(node.get());

	//创建位置变换节点pat2
	osg::ref_ptr<osg::PositionAttitudeTransform> pat2 = new osg::PositionAttitudeTransform();
	//设置位置为osg::Vec3(10.0f,0.0f,0.0f)
	pat2->setPosition(osg::Vec3(10.0f,0.0f,0.0f));
	//添加子节点
	pat2->addChild(node.get());

	//创建位置变换节点pat1
	osg::ref_ptr<osg::PositionAttitudeTransform> pat3 = new osg::PositionAttitudeTransform() ;
	//设置位置为osg::Vec3(-10.0f,0.0f,0.0f)
	pat3->setPosition(osg::Vec3(10.0f, 5.0f, -2.0f));
	//设置缩放,在X,Y,Z方向都缩小一倍
	pat3->setScale(osg::Vec3(0.4f,0.4f,0.4f));
	//添加子节点
	pat3->addChild(node.get());

	osg::Group* pgroup = new osg::Group;
	//添加到场景
	pgroup->addChild(pat1);
	pgroup->addChild(pat2);
	pgroup->addChild(pat3);

	/*//自动缩放处理
	osg::AutoTransform * tatf = new osg::AutoTransform;
	tatf->setAutoScaleToScreen(true);
	tatf->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
	tatf->setMinimumScale(1.0f);
	tatf->setMaximumScale(10.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> pat4 = new osg::PositionAttitudeTransform() ;
	pat4->addChild(pgroup);
	pat4->setScale(osg::Vec3(70.4f,70.4f,70.4f));
	//添加子节点
	tatf->addChild(pat4);*/

	root->addChild(pgroup);

	return root.release();
}

