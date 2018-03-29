
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>
#include <osgGA/EventVisitor>

#include <osgUtil/Optimizer>

//继承自osg::NodeCallback类，写一个事件回调类
class MyEventCallback : public osg::NodeCallback
{
public:

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{ 
		//判断访问器类型
		if (nv->getVisitorType()==osg::NodeVisitor::EVENT_VISITOR)
		{	
			//创建一个事件访问器并初始化
			osg::ref_ptr<osgGA::EventVisitor> ev = dynamic_cast<osgGA::EventVisitor*>(nv);
			if (ev)
			{
				//得到执行动作
				osgGA::GUIActionAdapter* aa = ev->getActionAdapter();
				//得到事件队列
				osgGA::EventQueue::Events& events = ev->getEvents();

				for(osgGA::EventQueue::Events::iterator itr=events.begin();
					itr!=events.end(); ++itr)
				{
					//处理事件
					osgGA::GUIEventAdapter* pEvent = dynamic_cast<osgGA::GUIEventAdapter*>((*itr).get());
					if (pEvent)
					{
						handle(*pEvent,*(aa));
					}
				}
			}
		}
	}

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{ 
		//得到场景数据
		osg::ref_ptr<osgViewer::Viewer> viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		osg::ref_ptr<osg::MatrixTransform> mt = dynamic_cast<osg::MatrixTransform*>(viewer->getSceneData());

		switch(ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				//按下Key_Up时,向Z正方向平移一个单位
				if (ea.getKey()==osgGA::GUIEventAdapter::KEY_Up)
				{
					osg::Matrix mT ;
					mT.makeTranslate(0.0f,0.0f,1.0f);
					mt->setMatrix(mT);
				}

				//按下Key_Down时，向Z负方向平移一个单位
				if(ea.getKey()==osgGA::GUIEventAdapter::KEY_Down)
				{
					osg::Matrix mT ;
					mT.makeTranslate(0.0f,0.0f,-1.0f);
					mt->setMatrix(mT);
				}
				break;
			}
		default:

			break;
		}
		return false;
	}
};


int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	//加载牛的模型，注意需要创建osg::MatrixTransform矩阵变换对象
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	//创建矩阵变换节点
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	mt->addChild(node.get());

	//得到相机
	osg::ref_ptr<osg::Camera> camera  = viewer->getCamera();

	//设置相机事件回调
	camera->setEventCallback(new MyEventCallback());

	//优化场景数据
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(mt.get());

	viewer->setSceneData(mt.get());

	viewer->realize();

	viewer->run();

	return 0 ;
}