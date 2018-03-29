
#include <osg/Geode>
#include <osg/Group>
#include <osg/Notify>
#include <osg/BlendEquation>

#include <osgDB/Registry>
#include <osgDB/ReadFile>

#include <osgUtil/Optimizer>

#include <osgViewer/Viewer>
#include <osgUtil/SmoothingVisitor>
#include <iostream>
#include "osg/Vec4"

osg::ref_ptr<osg::Drawable> createHouseWall()
{
	//House Vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back(osg::Vec3(0, 0, 4));
	vertices->push_back(osg::Vec3(0, 0, 0));
	vertices->push_back(osg::Vec3(6, 0, 4));
	vertices->push_back(osg::Vec3(6, 0, 0));
	vertices->push_back(osg::Vec3(6, 4, 4));
	vertices->push_back(osg::Vec3(6, 4, 0));
	vertices->push_back(osg::Vec3(0, 4, 4));
	vertices->push_back(osg::Vec3(0, 4, 0));
	vertices->push_back(osg::Vec3(0, 0, 4));
	vertices->push_back(osg::Vec3(0, 0, 0));

	//normals
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
// 	normals->push_back(osg::Vec3(-1, -1, 0));
// 	normals->push_back(osg::Vec3(-1, -1, 0));
// 	normals->push_back(osg::Vec3(1, -1, 0));
// 	normals->push_back(osg::Vec3(1, -1, 0));
// 	normals->push_back(osg::Vec3(1, 1, 0));
// 	normals->push_back(osg::Vec3(1, 1, 0));
// 	normals->push_back(osg::Vec3(-1, 1, 0));
// 	normals->push_back(osg::Vec3(-1, 1, 0));
// 	normals->push_back(osg::Vec3(-1, -1, 0));
// 	normals->push_back(osg::Vec3(-1, -1, 0));

	normals->push_back(osg::Vec3(-0.5, -0.5, 0));
	normals->push_back(osg::Vec3(-0.5, -0.5, 0));
	normals->push_back(osg::Vec3(0.5, -0.5, 0));
	normals->push_back(osg::Vec3(0.5, -0.5, 0));
	normals->push_back(osg::Vec3(0.5, 0.5, 0));
	normals->push_back(osg::Vec3(0.5, 0.5, 0));
	normals->push_back(osg::Vec3(-0.5, 0.5, 0));
	normals->push_back(osg::Vec3(-0.5, 0.5, 0));
	normals->push_back(osg::Vec3(-0.5, -0.5, 0));
	normals->push_back(osg::Vec3(-0.5, -0.5, 0));

	osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array;
	texCoords->push_back(osg::Vec2(0.0, 1));
	texCoords->push_back(osg::Vec2(0.0, 0));
	texCoords->push_back(osg::Vec2(0.3, 1));
	texCoords->push_back(osg::Vec2(0.3, 0));
	texCoords->push_back(osg::Vec2(0.5, 1));
	texCoords->push_back(osg::Vec2(0.8, 1));
	texCoords->push_back(osg::Vec2(0.8, 0));
	texCoords->push_back(osg::Vec2(1, 1));
	texCoords->push_back(osg::Vec2(1, 0));

	osg::ref_ptr<osg::Geometry> houseWall = new osg::Geometry;
	houseWall->setVertexArray(vertices);
	houseWall->setNormalArray(normals);
	houseWall->setTexCoordArray(0, texCoords);
	houseWall->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	houseWall->addPrimitiveSet(
		new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, vertices->size()));

	osg::ref_ptr<osg::Image> img = osgDB::readRefImageFile("videowall.png");
	houseWall->getOrCreateStateSet()->setTextureAttribute(0,
		new osg::Texture2D(img));
	return houseWall;
}


osg::ref_ptr<osg::Drawable> createHouseRoof()
{
	//House Vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back( osg::Vec3(-0.2,-0.5, 3.5) );  // 0
	vertices->push_back( osg::Vec3( 6.2,-0.5, 3.5) );  // 1
	vertices->push_back( osg::Vec3( 0.8, 2.0, 6.0) );  // 2
	vertices->push_back( osg::Vec3( 5.2, 2.0, 6.0) );  // 3
	vertices->push_back( osg::Vec3(-0.2, 4.5, 3.5) );  // 4
	vertices->push_back( osg::Vec3( 6.2, 4.5, 3.5) );  // 5

	osg::ref_ptr<osg::DrawArrays> roof = 
		new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 6);

	osg::ref_ptr<osg::DrawElementsUInt> roofSide = 
		new osg::DrawElementsUInt(osg::DrawElementsUInt::TRIANGLES, 6);

	roofSide->push_back(0);
	roofSide->push_back(2);
	roofSide->push_back(4);
	roofSide->push_back(5);
	roofSide->push_back(3);
	roofSide->push_back(1);

	//color
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(0.25, 0, 0, 1));

	//
	osg::ref_ptr<osg::Geometry> houseRoof = new osg::Geometry;
	houseRoof->setVertexArray(vertices);
	houseRoof->setColorArray(colors);
	houseRoof->setColorBinding(osg::Geometry::BIND_OVERALL);
	houseRoof->addPrimitiveSet(roof);
	houseRoof->addPrimitiveSet(roofSide);
	osgUtil::SmoothingVisitor smv;
	smv.smooth(*houseRoof);

	return houseRoof;
}

int main( int argc, char **argv )
{
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Geode> root = new osg::Geode;    
	
	root->addDrawable(createHouseWall());
	root->addDrawable(createHouseRoof());
	osgUtil::Optimizer opt;
	opt.optimize(root);

	viewer.setSceneData( root );

	return viewer.run();
}
