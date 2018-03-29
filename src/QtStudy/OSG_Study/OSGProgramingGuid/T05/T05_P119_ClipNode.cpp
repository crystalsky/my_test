#include "T05_P119_ClipNode.h"
#include <osg/Geode>
#include <osg/Group>
#include <osgdb/ReadFile>
#include <osgdb/WriteFile>
#include <osgViewer/View>
#include <osgGA/StateSetManipulator>
#include "osgviewerQt.h"
#include "osg/MatrixTransform"
#include "osg/ClipNode"

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T05_P119_ClipNode, P119_ClipNode)
T05_P119_ClipNode::T05_P119_ClipNode()
{
    
}

T05_P119_ClipNode::~T05_P119_ClipNode()
{
    
}

void T05_P119_ClipNode::init()
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

void T05_P119_ClipNode::_doInit()
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


static osg::ref_ptr<osg::Node> createClipNode(osg::ref_ptr<osg::Node> subgraph)
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();

	//多边形线形绘制模式，正面和反面都绘制
	osg::ref_ptr<osg::PolygonMode> polymode = new osg::PolygonMode();
	polymode->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);

	//启用多边形线形绘制模式，并指定状态继承属性为OVERRIDE
	stateset->setAttributeAndModes(polymode, osg::StateAttribute::PROTECTED | osg::StateAttribute::ON);

	//多边形线形绘制节点
	osg::ref_ptr<osg::Group> wireframe_subgraph = new osg::Group;
	//设置渲染状态
	wireframe_subgraph->setStateSet(stateset.get());
	wireframe_subgraph->addChild(subgraph.get());

	root->addChild(wireframe_subgraph.get());

	osg::ref_ptr<osg::MatrixTransform> transform= new osg::MatrixTransform;
	//更新回调，实现动态裁剪
	osg::ref_ptr<osg::NodeCallback> nc = 
		new osg::AnimationPathCallback(
		subgraph->getBound().center(),
		osg::Vec3(0.0f,0.0f,1.0f),
		osg::inDegrees(90.0f));
	transform->setUpdateCallback(nc.get());

	//创建裁剪节点
	osg::ref_ptr<osg::ClipNode> clipnode = new osg::ClipNode;
	osg::BoundingSphere bs = subgraph->getBound();
	bs.radius() *= 0.5f;

	//设置裁剪节点的包围盒
	osg::BoundingBox bb;
	bb.expandBy(bs);

	//根据前面指定的包围盒创建六个裁剪平面
	clipnode->createClipBox(bb);
	//禁用拣选
	clipnode->setCullingActive(false);

	transform->addChild(clipnode.get());
	root->addChild(transform.get());

	//创建未被裁剪的节点
	osg::ref_ptr<osg::Group> clippedNode = new osg::Group;
	clippedNode->setStateSet(clipnode->getStateSet());
	clippedNode->addChild(subgraph.get());

	root->addChild(clippedNode.get());

	return root.get();
}


osg::Node* T05_P119_ClipNode::getNode()
{
    osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cessna.osg");
    //添加到场景
    root->addChild(createClipNode(node));

    return root.release();
}
