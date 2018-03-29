
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/NodeCallback>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

//��osg::NodeCallback�̳�һ�����࣬ʵ��spaceship�Ļص�
class SpaceShipCallback :public osg::NodeCallback
{
public:
	SpaceShipCallback():angle(0)
	{
		//
	}

	virtual void operator()(osg::Node* node ,osg::NodeVisitor* nv)
	{
		//��������任�ڵ�
		osg::ref_ptr<osg::MatrixTransform> mtCow = dynamic_cast<osg::MatrixTransform*>(node);
		//��������
		osg::Matrix mr ;
		//��ת����Z�ᣬÿ����תangle�Ƕ�
		mr.makeRotate(angle,osg::Vec3(0.0f,0,1.0f));
		//���þ���
		mtCow->setMatrix(mr);

		angle+= 0.01 ;

		//�������ݲ�����ִ���������ûص��Ľڵ�
		traverse( node, nv );
	}

public:

	//��ת�Ƕ�
	double angle ;
};
int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer() ;

	osg::ref_ptr<osg::Group> root = new osg::Group() ;

	//��ȡ��ţģ��
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg") ;

	//��������任�ڵ�
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform() ;
	mt->addChild(node.get()) ;
	//���ø��»ص�
	mt->setUpdateCallback(new SpaceShipCallback());

	root->addChild(mt.get()) ;

	//�Ż���������
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root.get()) ;

	viewer->setSceneData(root.get()) ;

	viewer->realize() ;

	viewer->run() ;

	return 0 ;
}