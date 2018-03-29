#ifndef osgviewerQt_h__
#define osgviewerQt_h__

#include <QTimer>
#include <QApplication>
#include <QGridLayout>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>

#include <osgDB/ReadFile>

#include <osgQt/GraphicsWindowQt>

#include <iostream>

class ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
public:
    ViewerWidget(osgViewer::ViewerBase::ThreadingModel threadingModel=osgViewer::CompositeViewer::SingleThreaded) : QWidget()
    {
        setThreadingModel(threadingModel);

        // disable the default setting of viewer.done() by pressing Escape.
        setKeyEventSetsDone(0);

        m_pWidget = createViewWidget();
  
        QVBoxLayout* grid = new QVBoxLayout;
		grid->setContentsMargins(2, 2, 2, 2);//这个不能设为全0,这样有问题???
        grid->addWidget( m_pWidget);
        setLayout( grid );

        connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
        _timer.start( 10 );
    }

	osgViewer::View* getViewer()const
	{
		return m_mapViewer.value(m_pWidget);
	}

	void setSceneData(osg::Node* pScene)
	{
		if (getViewer() != NULL)
		{
			getViewer()->setSceneData(pScene);
		}
	}

	void addEventHandler(osgGA::GUIEventHandler* pHander)
	{
		getViewer()->addEventHandler(pHander);
	}

	void clearEventHandlers()
	{
		osgViewer::Viewer::EventHandlers listHanders = 
			getViewer()->getEventHandlers();

		for (osgViewer::Viewer::EventHandlers::iterator i = listHanders.begin(); 
			i != listHanders.end(); ++i)
		{
			getViewer()->removeEventHandler(*i);
		}		
	}
protected:
	osgViewer::View* getViewer(QWidget* pWidget)
	{
		return m_mapViewer.value(pWidget);
	}

	QWidget* createViewWidget()
	{
		return createViewWidget( createGraphicsWindow(0,0,100,100), NULL);
	}

	QWidget* createViewWidget(osg::ref_ptr<osgViewer::View>& view)
	{
		return createViewWidget( createGraphicsWindow(0,0,100,100), view, NULL);
	}

	QWidget* createViewWidget( osgQt::GraphicsWindowQt* gw, osg::ref_ptr<osgViewer::View>& view, osg::Node* scene )
	{
		QWidget* pWidget = createViewWidget(gw, scene);

		view = getViewer(pWidget);
		
		return pWidget;
	}

	QWidget* createViewWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene )
	{
		osgViewer::Viewer* view = new osgViewer::Viewer;
		addView( view );

		osg::Camera* camera = view->getCamera();
		camera->setGraphicsContext( gw );

		const osg::GraphicsContext::Traits* traits = gw->getTraits();

		camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
		camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
		camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );

		view->setSceneData( scene );
		view->addEventHandler( new osgViewer::StatsHandler );
		view->setCameraManipulator( new osgGA::TrackballManipulator );

		QWidget* pWidget = gw->getGLWidget();
		m_mapViewer[pWidget] = view;

		return pWidget;
	}

    osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false )
    {
        osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
        traits->windowName = name;
        traits->windowDecoration = windowDecoration;
        traits->x = x;
        traits->y = y;
        traits->width = w;
        traits->height = h;
        traits->doubleBuffer = true;
        traits->alpha = ds->getMinimumNumAlphaBits();
        traits->stencil = ds->getMinimumNumStencilBits();
        traits->sampleBuffers = ds->getMultiSamples();
        traits->samples = ds->getNumMultiSamples();

        return new osgQt::GraphicsWindowQt(traits.get());
    }

    virtual void paintEvent( QPaintEvent* event )
    { frame(); }

protected:
	QMap<QWidget*, osgViewer::Viewer*>	m_mapViewer;
    QTimer _timer;
	QWidget* m_pWidget;
};
#endif // osgviewerQt_h__