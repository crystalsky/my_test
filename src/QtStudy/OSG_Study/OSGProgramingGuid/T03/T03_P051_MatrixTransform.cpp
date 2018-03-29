#include "T03_P051_MatrixTransform.h"
#include "osg/Group"
#include <osgdb/ReadFile>
#include <osg/MatrixTransform>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T03_P051_MatrixTransform, P051_MatrixTransform)
T03_P051_MatrixTransform::T03_P051_MatrixTransform()
{
	
}

T03_P051_MatrixTransform::~T03_P051_MatrixTransform()
{
	
}

osg::Node* T03_P051_MatrixTransform::getNode()
{
	//����������ڵ�
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//����һ���ڵ�,��ȡţ��ģ��
	osg::ref_ptr<osg::Node> node =osgDB::readNodeFile("cow.osg");

	//��������任�ڵ�mt1
	osg::ref_ptr<osg::MatrixTransform> mt1 = new osg::MatrixTransform() ;
	//����һ������
	osg::Matrix m;
	//��X����ƽ��10����λ
	m.makeTranslate(osg::Vec3(10.0f,0.0f,0.0f));
	//��X����ת45��
	m.makeRotate(45.0f,1.0f,0.0f,0.0f);
	//���þ���
	mt1->setMatrix(m);
	//����ӽڵ�
	mt1->addChild(node.get());

	//��������任�ڵ�mt2
	osg::ref_ptr<osg::MatrixTransform> mt2 = new osg::MatrixTransform();
	//����һ������
	osg::Matrix t ;
	//��X��������ƽ��10����λ
	t.makeTranslate(osg::Vec3(-10.0f,0.0f,0.0f));
	//���þ���
	mt2->setMatrix(t);
	//����ӽڵ�
	mt2->addChild(node.get());

	//��ӵ�����
	root->addChild(mt1.get());
	root->addChild(mt2.get());

	return root.release();
}

