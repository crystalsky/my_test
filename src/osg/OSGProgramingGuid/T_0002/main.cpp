
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

//�̳���osg::NodeCallback�࣬дһ���¼��ص���
class MyEventCallback : public osg::NodeCallback
{
public:

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{ 
		//�жϷ���������
		if (nv->getVisitorType()==osg::NodeVisitor::EVENT_VISITOR)
		{	
			//����һ���¼�����������ʼ��
			osg::ref_ptr<osgGA::EventVisitor> ev = dynamic_cast<osgGA::EventVisitor*>(nv);
			if (ev)
			{
				//�õ�ִ�ж���
				osgGA::GUIActionAdapter* aa = ev->getActionAdapter();
				//�õ��¼�����
				osgGA::EventQueue::Events& events = ev->getEvents();

				for(osgGA::EventQueue::Events::iterator itr=events.begin();
					itr!=events.end(); ++itr)
				{
					//�����¼�
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
		//�õ���������
		osg::ref_ptr<osgViewer::Viewer> viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		osg::ref_ptr<osg::MatrixTransform> mt = dynamic_cast<osg::MatrixTransform*>(viewer->getSceneData());

		switch(ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				//����Key_Upʱ,��Z������ƽ��һ����λ
				if (ea.getKey()==osgGA::GUIEventAdapter::KEY_Up)
				{
					osg::Matrix mT ;
					mT.makeTranslate(0.0f,0.0f,1.0f);
					mt->setMatrix(mT);
				}

				//����Key_Downʱ����Z������ƽ��һ����λ
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

	//����ţ��ģ�ͣ�ע����Ҫ����osg::MatrixTransform����任����
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	//��������任�ڵ�
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	mt->addChild(node.get());

	//�õ����
	osg::ref_ptr<osg::Camera> camera  = viewer->getCamera();

	//��������¼��ص�
	camera->setEventCallback(new MyEventCallback());

	//�Ż���������
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(mt.get());

	viewer->setSceneData(mt.get());

	viewer->realize();

	viewer->run();

	return 0 ;
}