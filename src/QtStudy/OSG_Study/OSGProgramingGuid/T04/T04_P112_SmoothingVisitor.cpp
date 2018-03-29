#include "T04_P112_SmoothingVisitor.h"
#include <osg/Geode>
#include <osg/Group>
#include <osgdb/ReadFile>
#include <osgdb/WriteFile>
#include <osgViewer/View>
#include <osgGA/StateSetManipulator>
#include "osgviewerQt.h"
#include "osgUtil/SmoothingVisitor"

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T04_P112_SmoothingVisitor, P112_SmoothingVisitor)
T04_P112_SmoothingVisitor::T04_P112_SmoothingVisitor()
{
    
}

T04_P112_SmoothingVisitor::~T04_P112_SmoothingVisitor()
{
    
}

void T04_P112_SmoothingVisitor::init()
{
    if (m_bInit)
    {
        return;
    }

    //初始化ViewerWidget
    _initOwnViewerWidget(false);

    _doInit();

    m_bInit = true;
}

void T04_P112_SmoothingVisitor::_doInit()
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
static osg::ref_ptr<osg::Geometry> createQuad()
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

	//添加图元，绘图基元为四边形
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	return geom.get() ;
}


osg::Node* T04_P112_SmoothingVisitor::getNode()
{
    osg::ref_ptr<osg::Group> root = new osg::Group();

    //添加到场景
	//创建一个几何体对象,注意，几何体并没有指定法线
	//如果你注释下面生成顶点法线的代码，你就可以看到
	//光照的差别
	osg::ref_ptr<osg::Geometry> geometry = createQuad();

	//生成顶点法线
	osgUtil::SmoothingVisitor::smooth(*(geometry.get()));

	//添加到叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geometry.get());

	//添加到场景
	root->addChild(geode.get());

    return root.release();
}
