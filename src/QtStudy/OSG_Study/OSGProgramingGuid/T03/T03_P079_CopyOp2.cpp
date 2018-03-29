#include "T03_P079_CopyOp2.h"

#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geometry>
#include <osg/Image>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Notify>
#include <osg/Texture>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <iostream>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T03_P079_CopyOp2, P079_CopyOp2)
T03_P079_CopyOp2::T03_P079_CopyOp2()
{
	
}

T03_P079_CopyOp2::~T03_P079_CopyOp2()
{
	
}

//�Զ���Copy�࣬�������������Ϣ
class GraphCopyOp : public osg::CopyOp
{
public:
	inline GraphCopyOp
		(CopyFlags flags=SHALLOW_COPY):
	osg::CopyOp(flags) 
	{ 
		_nodeCopyMap.clear();
	}

	//�ڵ��copy
	virtual osg::Node* operator() (const osg::Node* node) const
	{
		//�ж��Ƿ�Ϊ���
		if (node && _flags&DEEP_COPY_NODES)
		{
			//�жϽڵ�ĸ��ڵ��Ƿ��ж�������ֻ��һ������ֱ�����
			if ( node->getNumParents() > 1 )
			{
				//�ж��Ƿ��Ѿ�����
				if ( _nodeCopyMap.find(node) != _nodeCopyMap.end() )
				{
					std::cout<<"Copy of node "<<node<<" "<<node->getName()<<", "
						<< _nodeCopyMap[node]<<", will be reused"<<std::endl;
					//ֱ�ӷ��ؿ�������ĵ�ַ
					return (osg::Node*)(_nodeCopyMap[node]);
				}
				else
				{	
					//���п�������ӳ����б��濽������
					osg::Node* newNode = dynamic_cast<osg::Node*>( node->clone(*this) );
					_nodeCopyMap[node] = newNode;
					//���ص�ַ
					return newNode;
				}
			}
			else
			{
				//ֱ�ӿ���
				return dynamic_cast<osg::Node*>( node->clone(*this) );
			}
		}
		else
		{
			//ֱ�ӷ��ص�ַ
			return const_cast<osg::Node*>(node);
		}
	}

protected:

	//�ڵ�ӳ�����������child�Ϳ������ֱ���Ϊԭ�����
	mutable std::map<const osg::Node*,osg::Node*> _nodeCopyMap;
};

osg::Node* T03_P079_CopyOp2::getNode()
{
	//����һ���ุ�ڵ㹲��һ���ӽڵ�ĳ���
	osg::ref_ptr<osg::Group> rootnode = new osg::Group() ;

	osg::ref_ptr<osg::Node> node =osgDB::readNodeFile("glider.osg");

	//�ӽڵ�pat������node
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform() ;
	pat->setPosition(osg::Vec3(5.0f,0.0f,0.0f));
	pat->addChild(node.get());

	//�ӽڵ�mt������node
	osg::ref_ptr<osg::MatrixTransform> mt =new osg::MatrixTransform() ;
	osg::Matrix m ;
	m.makeScale(2.0f,2.0f,2.0f);
	mt->setMatrix(m);
	mt->addChild(node.get());

	//����ӽڵ�
	rootnode->addChild(pat.get());
	rootnode->addChild(mt.get());

	//һ���ุ�ڵ�һ���ӽڵ�ĳ�����Ĭ�����
	osg::ref_ptr<osg::Node> deepCopy = dynamic_cast<osg::Node*>(rootnode->clone(osg::CopyOp::DEEP_COPY_ALL));
	std::cout <<std::endl << "���һ���ุ�ڵ�һ���ӽڵ�ĳ�����Ĭ�����" <<std::endl<<std::endl ;
	osgDB::writeNodeFile(*(deepCopy.get()),"deepCopy.osg");

	//���һ���ุ�ڵ�һ���ӽڵ�ĳ�����ǳ����
	osg::ref_ptr<osg::Node> myShallowCopy = dynamic_cast<osg::Node*>(rootnode->clone(GraphCopyOp(osg::CopyOp::SHALLOW_COPY)));
	std::cout <<std::endl << "���һ���ุ�ڵ�һ���ӽڵ�ĳ�����ǳ����" <<std::endl<<std::endl ;
	osgDB::writeNodeFile(*(myShallowCopy.get()),"myShallowCopy.osg");

	//���һ���ุ�ڵ�һ���ӽڵ�ĳ��������
	osg::ref_ptr<osg::Node> myDeepCopy = dynamic_cast<osg::Node*>(rootnode->clone(GraphCopyOp(osg::CopyOp::DEEP_COPY_ALL)));
	std::cout <<std::endl << "���һ���ุ�ڵ�һ���ӽڵ�ĳ��������" <<std::endl<<std::endl ;
	osgDB::writeNodeFile(*(myDeepCopy.get()),"myDeepCopy.osg");

	return rootnode.release();
}

