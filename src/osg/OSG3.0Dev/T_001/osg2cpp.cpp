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
			//�������㣬��ʱ�ڵ�·��Ҳ��¼����
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

	//��Ⱦ״̬����
	viewer->addEventHandler(
		new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));//w/l/b/t

	//�ı��߳�ģʽ
	viewer->addEventHandler(new osgViewer::ThreadingHandler);//e/m

	//���ڴ�С�ͷֱ��ʸı�
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);//f shift+> shift+<

	//������Ϣ
	viewer->addEventHandler(new osgViewer::HelpHandler);//h

	//��¼Camera·��
	viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);//z->Z

	//��ȾLOGϸ��
	viewer->addEventHandler(new osgViewer::LODScaleHandler);

	//��ͼ
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
