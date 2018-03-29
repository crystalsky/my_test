
#include <osg/Geode>
#include <osg/Group>
#include <osg/Notify>
#include <osg/BlendEquation>

#include <osgDB/Registry>
#include <osgDB/ReadFile>

#include <osgUtil/Optimizer>

#include <osgViewer/Viewer>

#include <iostream>

osg::ref_ptr<osg::Node> createQuad()
{
	//Ҷ���
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	//������
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//��������
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0, 0, 0));
	v->push_back(osg::Vec3(1, 0, 0));
	v->push_back(osg::Vec3(1, 0, 1));
	v->push_back(osg::Vec3(0, 0, 1));
	v->push_back(osg::Vec3(0, -1, 0));
	geom->setVertexArray(v);

	//�ı�����������
	osg::ref_ptr<osg::DrawElementsUInt> quad = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	quad->push_back(0);
	quad->push_back(1);
	quad->push_back(2);
	quad->push_back(3);
	geom->addPrimitiveSet(quad);


	//������������
	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;
	vt->push_back(osg::Vec2(0, 0));
	vt->push_back(osg::Vec2(1, 0));
	vt->push_back(osg::Vec2(1, 1));
	vt->push_back(osg::Vec2(0, 1));
	geom->setTexCoordArray(0, vt);

	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array;
	vc->push_back(osg::Vec4(1, 0, 0, 1));
	vc->push_back(osg::Vec4(0, 1, 0, 1));
	vc->push_back(osg::Vec4(0, 0, 1, 1));
	vc->push_back(osg::Vec4(1, 1, 0, 0));
	geom->setColorArray(vc);
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);//�󶨵�������

	//����
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array;
	nc->push_back(osg::Vec3(0, -1, 0));
	geom->setNormalArray(nc);
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);//ȫ�������

	//
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));


	geode->addDrawable(geom.get());

	return geode.get();
}

int main( int argc, char **argv )
{
	osgViewer::Viewer viewer;
	osg::Group* root = new osg::Group;    
	
	root->addChild(createQuad());

	osgUtil::Optimizer opt;
	opt.optimize(root);

	viewer.setSceneData( root );

	return viewer.run();
}
