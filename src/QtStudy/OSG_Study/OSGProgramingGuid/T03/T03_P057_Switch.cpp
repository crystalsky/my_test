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

	//����һ���ڵ�,��ȡţ��ģ��
	osg::ref_ptr<osg::Node> node1 = new osg::Node();
	node1 = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr<osg::MatrixTransform> mxGlider = new osg::MatrixTransform;
	mxGlider->addChild(node1);
	osg::Matrix mx;
	mx.makeTranslate(osg::Vec3d(10.0f, 1.0f, 0));
	mx.rotate(45.9, osg::Vec3f(1, 0, 1.0));
	mxGlider->setMatrix(mx);

	//����һ���ڵ㣬��ȡ�����ģ��
	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg") ;

	//����һ�����ؽڵ㣬ֻ��Ⱦ�����������Ⱦţ
	osg::ref_ptr<osg::Switch> swtich =  new osg::Switch();
	//���ţ��ģ�ͣ�������Ⱦ��Ĭ��Ϊtrue
	swtich->addChild(mxGlider.get(),true);
	//��ӻ����ģ�ͣ�״̬Ϊ��Ⱦ
	swtich->addChild(node2.get(),true);

	root->addChild(swtich.get());

	return root.release();
}

