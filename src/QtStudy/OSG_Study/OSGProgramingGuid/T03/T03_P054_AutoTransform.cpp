#include "T03_P054_AutoTransform.h"
#include <osg/Geode>
#include <osg/AutoTransform>
#include <osgText/Text>

IMPLEMENT_REFLECTED_CLASS_SPECIFY_NAME(T03_P054_AutoTransform, P054_AutoTransform)
T03_P054_AutoTransform::T03_P054_AutoTransform()
{
	
}

T03_P054_AutoTransform::~T03_P054_AutoTransform()
{
	
}

//�����Զ��任�ڵ�
osg::ref_ptr<osg::Node> createAutoTransform(osg::Vec3& position,float size,std::string& label,
											osg::AutoTransform::AutoRotateMode autoMode,osgText::Text::AxisAlignment axisAlignment)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	//����
	std::string font("fonts/cour.ttf") ;

	//����Text����
	osg::ref_ptr<osgText::Text> text = new osgText::Text();
	geode->addDrawable(text.get()) ;

	//��������
	text->setFont(font) ;
	//��������ķֱ��ʣ�Ĭ��Ϊ32*32
	text->setFontResolution(128.0f,128.0f) ;
	//��������Ĵ�С
	text->setCharacterSize(size) ;
	//���ö��뷽ʽ
	text->setAlignment(osgText::Text::CENTER_CENTER ) ;
	//���÷���
	text->setAxisAlignment(axisAlignment) ;
	//��������
	text->setText(label) ;

	//�رչ���
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF) ;

	//�����Զ��任�ڵ�
	osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform() ;
	//����ӽڵ�
	at->addChild(geode) ;

	//�����Զ��任��ʽ
	at->setAutoRotateMode(autoMode) ;
	//������Ļ��С�����Žڵ㣬Ĭ��Ϊfalse������Ϊtrueʱ���ڵ��޷�����
	at->setAutoScaleToScreen(false) ;
	//at->setAutoScaleToScreen(true) ;
	//�������ŵ�������С����
	at->setMinimumScale(0.0f) ;
	at->setMaximumScale(5.0f) ;
	//����λ��
	at->setPosition(position) ;

	return at;
}


osg::Node* T03_P054_AutoTransform::getNode()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	root->addChild(createAutoTransform(
		osg::Vec3(0,0,0), 
		60.0f, 
		std::string("Fly To Sky"),
		osg::AutoTransform::ROTATE_TO_SCREEN,
		osgText::Text::XY_PLANE));

	/*root->addChild(createAutoTransform(
		osg::Vec3(0,0,0), 
		60.0f, 
		std::string("Fly To Sky"),
		osg::AutoTransform::NO_ROTATION,
		osgText::Text::YZ_PLANE));*/

	/*root->addChild(createAutoTransform(
		osg::Vec3(0,0,0), 
		60.0f, 
		std::string("Fly To Sky"),
		osg::AutoTransform::ROTATE_TO_CAMERA,
		osgText::Text::XY_PLANE));*/

	return root.release();
}

