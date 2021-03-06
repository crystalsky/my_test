#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

int main()
{
	//创建Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

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

	//添加到场景
	root->addChild(pat1.get());
	root->addChild(pat2.get());
	root->addChild(pat3);
	//优化场景数据
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root.get()) ;

	//设置场景数据
	viewer->setSceneData(root.get());
	//初始化并创建窗口
	viewer->realize();
	//开始渲染
	viewer->run();

	return 0 ;
}