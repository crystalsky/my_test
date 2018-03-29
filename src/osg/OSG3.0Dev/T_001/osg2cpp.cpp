#include "osgViewer/Viewer"
#include "osg/Node"
#include "osg/Geode"
#include "osg/Group"
#include "osgGA/StateSetManipulator"
#include "osgDB/ReadFile"
#include "osgdb/WriteFile"
#include "osgUtil/Optimizer"
#include "FrameRateDisplay.h"
#include "osgViewer/ViewerEventHandlers"
//TODO:
class GetWorldCoordinateOfNodeVisitor : public osg::NodeVisitor
{
public:
	GetWorldCoordinateOfNodeVisitor()
		: osg::NodeVisitor(NodeVisitor::TRAVERSE_PARENTS)
		, bDone(false)
	{
		wcMatrix = new osg::Matrixd();
	}

	virtual void apply(osg::Node& node)
	{
		if (!bDone)
		{
			//到达根结点，此时节点路径也记录完整
			if (0 == node.getNumParents())
			{
				wcMatrix->set(osg::computeLocalToWorld(this->getNodePath()));
				bDone = true;
			}

			traverse(node);
		}
	}

	osg::Matrixd* giveUpDaMat()
	{
		return wcMatrix;
	}

private:
	bool bDone;
	osg::Matrix* wcMatrix;
};

osg::Matrixd* getWorldCoords(osg::Node& node)
{
	GetWorldCoordinateOfNodeVisitor* ncv = new GetWorldCoordinateOfNodeVisitor();
	if (ncv)
	{
		node.accept(*ncv);
		return ncv->giveUpDaMat();
	}
	return NULL;
}

int main( int argc, char **argv )
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ArgumentParser arguments(&argc, argv);
	arguments.getApplicationUsage()->setApplicationName(arguments.getApplicationName());
	arguments.getApplicationUsage()->setDescription("Help Information");

#if 0
	viewer->addEventHandler(new osgViewer::StatsHandler);//s
#else
	viewer->addEventHandler(new FrameRateDisplay);//s
#endif

	//渲染状态控制
	viewer->addEventHandler(
		new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));//w/l/b/t

	//改变线程模式
	viewer->addEventHandler(new osgViewer::ThreadingHandler);//e/m

	//窗口大小和分辨率改变
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);//f shift+> shift+<

	//帮助信息
	viewer->addEventHandler(new osgViewer::HelpHandler);//h

	//记录Camera路径
	viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);//z->Z

	//渲染LOG细节
	viewer->addEventHandler(new osgViewer::LODScaleHandler);

	//切图
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);//c->C

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	root->addChild(node.get());

	osgUtil::Optimizer opt;
	opt.optimize(root.get());

	viewer->setSceneData(root.get());

	viewer->realize();

	viewer->run();

	return 0;
}
