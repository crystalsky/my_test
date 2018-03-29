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
	//创建场景组节点
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//创建一个节点,读取牛的模型
	osg::ref_ptr<osg::Node> node =osgDB::readNodeFile("cow.osg");

	//创建矩阵变换节点mt1
	osg::ref_ptr<osg::MatrixTransform> mt1 = new osg::MatrixTransform() ;
	//创建一个矩阵
	osg::Matrix m;
	//在X方向平移10个单位
	m.makeTranslate(osg::Vec3(10.0f,0.0f,0.0f));
	//绕X轴旋转45度
	m.makeRotate(45.0f,1.0f,0.0f,0.0f);
	//设置矩阵
	mt1->setMatrix(m);
	//添加子节点
	mt1->addChild(node.get());

	//创建矩阵变换节点mt2
	osg::ref_ptr<osg::MatrixTransform> mt2 = new osg::MatrixTransform();
	//创建一个矩阵
	osg::Matrix t ;
	//在X负方向上平移10个单位
	t.makeTranslate(osg::Vec3(-10.0f,0.0f,0.0f));
	//设置矩阵
	mt2->setMatrix(t);
	//添加子节点
	mt2->addChild(node.get());

	//添加到场景
	root->addChild(mt1.get());
	root->addChild(mt2.get());

	return root.release();
}

