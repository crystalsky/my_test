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
	//����Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	//����������ڵ�
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//����һ���ڵ�,��ȡţ��ģ��
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	//����λ�ñ任�ڵ�pat1
	osg::ref_ptr<osg::PositionAttitudeTransform> pat1 = new osg::PositionAttitudeTransform() ;
	//����λ��Ϊosg::Vec3(-10.0f,0.0f,0.0f)
	pat1->setPosition(osg::Vec3(10.0f,-5.0f,-2.0f));
	//��������,��X,Y,Z������Сһ��
	pat1->setScale(osg::Vec3(0.3f,0.3f,0.3f));
	//����ӽڵ�
	pat1->addChild(node.get());

	//����λ�ñ任�ڵ�pat2
	osg::ref_ptr<osg::PositionAttitudeTransform> pat2 = new osg::PositionAttitudeTransform();
	//����λ��Ϊosg::Vec3(10.0f,0.0f,0.0f)
	pat2->setPosition(osg::Vec3(10.0f,0.0f,0.0f));
	//����ӽڵ�
	pat2->addChild(node.get());

	//����λ�ñ任�ڵ�pat1
	osg::ref_ptr<osg::PositionAttitudeTransform> pat3 = new osg::PositionAttitudeTransform() ;
	//����λ��Ϊosg::Vec3(-10.0f,0.0f,0.0f)
	pat3->setPosition(osg::Vec3(10.0f, 5.0f, -2.0f));
	//��������,��X,Y,Z������Сһ��
	pat3->setScale(osg::Vec3(0.4f,0.4f,0.4f));
	//����ӽڵ�
	pat3->addChild(node.get());

	//��ӵ�����
	root->addChild(pat1.get());
	root->addChild(pat2.get());
	root->addChild(pat3);
	//�Ż���������
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root.get()) ;

	//���ó�������
	viewer->setSceneData(root.get());
	//��ʼ������������
	viewer->realize();
	//��ʼ��Ⱦ
	viewer->run();

	return 0 ;
}