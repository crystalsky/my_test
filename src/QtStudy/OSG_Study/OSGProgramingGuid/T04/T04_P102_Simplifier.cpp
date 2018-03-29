#include "T04_P102_Simplifier.h"
#include <osg/Geode>
#include <osg/Group>
#include <osgdb/ReadFile>
#include <osgdb/WriteFile>
#include "osgviewerQt.h"
#include "osgGA/StateSetManipulator"
#include "osgUtil/Simplifier"
#include "osg/PositionAttitudeTransform"
#include <TTimePrint.h>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T04_P102_Simplifier, P102_Simplifier)
T04_P102_Simplifier::T04_P102_Simplifier()
{
    
}

T04_P102_Simplifier::~T04_P102_Simplifier()
{
    
}

void T04_P102_Simplifier::init()
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

void T04_P102_Simplifier::_doInit()
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

osg::Node* T04_P102_Simplifier::getNode()
{
	TTRestart;
    osg::ref_ptr<osg::Group> root = new osg::Group();

	//设置样本比率，样本比率越大，简化越少
	//样本比率越小，简化越多
	float sampleRatio = 0.3f;
	//设置点的最大误差
	float maxError = 4.0f;

	//创建简化对象
	osgUtil::Simplifier simplifier(sampleRatio, maxError);

	//读取牛的模型
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");

	//深拷贝牛的模型到node2节点
	osg::ref_ptr<osg::Node> node2 = 
		(osg::Node*)(node1->clone(osg::CopyOp::DEEP_COPY_ALL));

	//创建一个位置变换节点
	osg::ref_ptr<osg::PositionAttitudeTransform> pat =
		new osg::PositionAttitudeTransform();
	//设置位置
	pat->setPosition(osg::Vec3(10.0f, 0.0f, 0.0f));
	//添加子节点
	pat->addChild(node2.get());

	pat->accept(simplifier);

	//添加到场景
	root->addChild(node1.get());
	root->addChild(pat.get());

	TTPrint(QStringLiteral("T04_P102_Simplifier"));

    return root.release();
}
