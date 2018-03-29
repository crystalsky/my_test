#include "T04_P108_TriStripVisitor.h"
#include <osg/Geode>
#include <osg/Group>
#include <osgdb/ReadFile>
#include <osgdb/WriteFile>
#include <osgViewer/View>
#include <osgGA/StateSetManipulator>
#include "osgviewerQt.h"
#include "osgUtil/TriStripVisitor"

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T04_P108_TriStripVisitor, P108_TriStripVisitor)
T04_P108_TriStripVisitor::T04_P108_TriStripVisitor()
{
    
}

T04_P108_TriStripVisitor::~T04_P108_TriStripVisitor()
{
    
}

void T04_P108_TriStripVisitor::init()
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

void T04_P108_TriStripVisitor::_doInit()
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


//创建一个四边形节点
osg::ref_ptr<osg::Geometry> createTriStripVisitorQuad()
{
	//创建一个叶节点对象
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	//创建一个几何体对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//创建顶点数组，注意顶点的添加顺序是逆时针的
	osg::ref_ptr<osg::Vec3Array> v= new osg::Vec3Array();
	//添加数据
	v->push_back(osg::Vec3(0.0f,0.0f,0.0f));
	v->push_back(osg::Vec3(1.0f,0.0f,0.0f));
	v->push_back(osg::Vec3(1.0f,0.0f,1.0f));
	v->push_back(osg::Vec3(0.0f,0.0f,1.0f));

	//设置顶点数据
	geom->setVertexArray(v.get());

	//创建纹理坐标
	osg::ref_ptr<osg::Vec2Array> vt= new osg::Vec2Array();
	//添加数据
	vt->push_back(osg::Vec2(0.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,1.0f));
	vt->push_back(osg::Vec2(0.0f,1.0f));

	//设置纹理坐标
	geom->setTexCoordArray(0,vt.get());

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	//添加数据
	vc->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
	vc->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
	vc->push_back(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
	vc->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f));

	//设置颜色数组
	geom->setColorArray(vc.get());
	//设置颜色的绑定方式为单个顶点
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//创建法线数组
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	//添加法线
	nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

	//设置法线数组
	geom->setNormalArray(nc.get());
	//设置法线的绑定方式为全部顶点
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	//添加图元，绘图基元为四边形
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	return geom.get() ;
}

osg::Node* T04_P108_TriStripVisitor::getNode()
{
    osg::ref_ptr<osg::Group> root = new osg::Group();

	//创建一个几何体对象
	osg::ref_ptr<osg::Geometry> geometry = createTriStripVisitorQuad();


	//对几何体进行条带化
	osgUtil::TriStripVisitor stripper ;
	stripper.stripify(*(geometry.get()));

	//添加到叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geometry.get());

    //添加到场景
    root->addChild(geode);

    return root.release();
}
