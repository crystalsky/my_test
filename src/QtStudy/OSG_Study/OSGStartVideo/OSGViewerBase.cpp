#include "OSGViewerBase.h"
#include <osg/Geode>
#include <osg/Group>
#include <osgdb/ReadFile>
#include <osgdb/WriteFile>
#include <osgViewer/View>
#include <osgGA/StateSetManipulator>
#include "osgviewerQt.h"

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(OSGViewerBase, T03_OSGViewerBase)
OSGViewerBase::OSGViewerBase()
{
    
}

OSGViewerBase::~OSGViewerBase()
{
    
}

void OSGViewerBase::init()
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

void OSGViewerBase::_doInit()
{
    ViewerWidget* pViewWidget = getViewerWidget();
    if (pViewWidget)
    {
        osgViewer::View* pView = pViewWidget->getViewer();

        //切换网格模式，方便比较模型的区别
        //pView->addEventHandler(
        //    new osgGA::StateSetManipulator(
        //    pView->getCamera()->getOrCreateStateSet()));

		pView->addEventHandler(new osgViewer::HelpHandler);
    }
}

osg::Node* OSGViewerBase::getNode()
{
    osg::ref_ptr<osg::Group> root = new osg::Group();

    //添加到场景
    root->addChild(osgDB::readNodeFile("glider.osg"));

    return root.release();
}
