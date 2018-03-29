#include "T04_P105_Delaunay.h"
#include <osg/Geode>
#include <osg/Group>
#include <osgdb/ReadFile>
#include <osgdb/WriteFile>
#include "osgViewer/View"
#include "osgGA/StateSetManipulator"
#include "Tex.h"
#include "osgviewerQt.h"
#include "osgUtil/DelaunayTriangulator"


IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T04_P105_Delaunay, P105_Delaunay)
T04_P105_Delaunay::T04_P105_Delaunay()
{
    
}

T04_P105_Delaunay::~T04_P105_Delaunay()
{
    
}

void T04_P105_Delaunay::init()
{
    if (m_bInit)
    {
        return;
    }

    //初始化ViewerWidget
    _initOwnViewerWidget(true);

    _doInit();

    m_bInit = true;
}

void T04_P105_Delaunay::_doInit()
{
	ViewerWidget* pViewWidget = getViewerWidget();
	if (pViewWidget)
	{
		osgViewer::View* pView = pViewWidget->getViewer();

		//切换网格模式，方便比较模型的区别
		pView->addEventHandler(
			new osgGA::StateSetManipulator(
			pView->getCamera()->getOrCreateStateSet()));
	}
}

osg::Node* T04_P105_Delaunay::getNode()
{
    osg::ref_ptr<osg::Group> root = new osg::Group();

	//创建顶点数组
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();

	//计算顶点数组的大小
	unsigned int n = sizeof(vertex)/sizeof(float[3]);

	//添加顶点数据
	for( unsigned int i = 0; i < n; i++ )
	{
		coords->push_back( osg::Vec3(vertex[i][0], vertex[i][1], vertex[i][2] ));
	}

	//创建Delaunay三角网对象
	osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = 
		new osgUtil::DelaunayTriangulator(coords);
	//生成三角网
	dt->triangulate();

	//创建几何体
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	//设置顶点数组
	geometry->setVertexArray(coords.get());

	//加入到绘图基元
	geometry->addPrimitiveSet(dt->getTriangles());

	//添加到叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable( geometry.get());

    //添加到场景
    root->addChild(geode);

    return root.release();
}
