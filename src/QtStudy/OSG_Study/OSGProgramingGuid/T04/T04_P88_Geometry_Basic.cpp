#include "T04_P88_Geometry_Basic.h"
#include <osg/Geode>
#include <osg/Group>
#include <osgdb/ReadFile>
#include <osgdb/WriteFile>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T04_P88_Geometry_Basic, P88_Geometry_Basic)
T04_P88_Geometry_Basic::T04_P88_Geometry_Basic()
{
	
}

T04_P88_Geometry_Basic::~T04_P88_Geometry_Basic()
{
	
}



osg::ref_ptr<osg::Node> createQuad1()
{
	//����һ��Ҷ�ڵ����
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	//����һ�����������
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//�����������飬ע�ⶥ������˳������ʱ���
	osg::ref_ptr<osg::Vec3Array> v= new osg::Vec3Array();
	//�������
	v->push_back(osg::Vec3(0.0f,0.0f,0.0f));
	v->push_back(osg::Vec3(1.0f,0.0f,0.0f));
	v->push_back(osg::Vec3(1.0f,0.0f,1.0f));
	v->push_back(osg::Vec3(0.0f,0.0f,1.0f));

	//���ö�������
	geom->setVertexArray(v.get());

	//������������
	osg::ref_ptr<osg::Vec2Array> vt= new osg::Vec2Array();
	//�������
	vt->push_back(osg::Vec2(0.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,1.0f));
	vt->push_back(osg::Vec2(0.0f,1.0f));

	//������������
	geom->setTexCoordArray(0,vt.get());

	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	//�������
	vc->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
	vc->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
	vc->push_back(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
	vc->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f));

	//������ɫ����
	geom->setColorArray(vc.get());
	//������ɫ�İ󶨷�ʽΪ��������
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//������������
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	//��ӷ���
	nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

	//���÷�������
	geom->setNormalArray(nc.get());
	//���÷��ߵİ󶨷�ʽΪȫ������
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	//���ͼԪ����ͼ��ԪΪ�ı���
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	//��ӵ�Ҷ�ڵ�
	geode->addDrawable(geom.get());

	return geode.get();
}

osg::Node* T04_P88_Geometry_Basic::getNode()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//��ӵ�����
	root->addChild(createQuad1());

	return root.release();
}



