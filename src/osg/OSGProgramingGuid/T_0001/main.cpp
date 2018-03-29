
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/NodeCallback>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

//从osg::NodeCallback继承一个新类，实现spaceship的回调
class SpaceShipCallback :public osg::NodeCallback
{
public:
	SpaceShipCallback():angle(0)
	{
		//
	}

	virtual void operator()(osg::Node* node ,osg::NodeVisitor* nv)
	{
		//创建矩阵变换节点
		osg::ref_ptr<osg::MatrixTransform> mtCow = dynamic_cast<osg::MatrixTransform*>(node);
		//创建矩阵
		osg::Matrix mr ;
		//旋转，绕Z轴，每次旋转angle角度
		mr.makeRotate(angle,osg::Vec3(0.0f,0,1.0f));
		//设置矩阵
		mtCow->setMatrix(mr);

		angle+= 0.01 ;

		//继续传递参数，执行其他设置回调的节点
		traverse( node, nv );
	}

public:

	//旋转角度
	double angle ;
};
int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer() ;

	osg::ref_ptr<osg::Group> root = new osg::Group() ;

	//读取奶牛模型
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg") ;

	//创建矩阵变换节点
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform() ;
	mt->addChild(node.get()) ;
	//设置更新回调
	mt->setUpdateCallback(new SpaceShipCallback());

	root->addChild(mt.get()) ;

	//优化场景数据
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root.get()) ;

	viewer->setSceneData(root.get()) ;

	viewer->realize() ;

	viewer->run() ;

	return 0 ;
}