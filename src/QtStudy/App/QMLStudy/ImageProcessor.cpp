#include "ImageProcessor.h"
#include <QDateTime>
#include "qqml.h"
#include <QQmlContext>
#include <QPointer>
#include <QCoreApplication>
#include <QThreadPool>


namespace Study_QML
{
	typedef void(*AlgorithmFuction)(const QString& srcFile, const QString& strDestFile);

	class AlgorithmRunnable;
	class ExcuteEvent : public QEvent
	{
	public:
		ExcuteEvent(AlgorithmRunnable* r)
			: QEvent(evType())
			, m_pRunnable(r)
		{
			assert(m_pRunnable != NULL);
		}

		static QEvent::Type evType()
		{
			if (m_evType == QEvent::None)
			{
				m_evType = static_cast<QEvent::Type>(registerEventType());
			}

			return m_evType;
		}

		AlgorithmRunnable* runnableObj()const {return m_pRunnable;}
	private:
		static QEvent::Type m_evType;
		AlgorithmRunnable* m_pRunnable;
	};
	QEvent::Type ExcuteEvent::m_evType = QEvent::None;

	static AlgorithmFuction g_sFunction[ImageProcessor::AlgorithmCount] =
	{
		PictureProcessorAlgorithm::_gray,
		PictureProcessorAlgorithm::_binarize,
		PictureProcessorAlgorithm::_negative,
		PictureProcessorAlgorithm::_emboss,
		PictureProcessorAlgorithm::_shapen,
		PictureProcessorAlgorithm::_soften
	};

	class AlgorithmRunnable : public QRunnable
	{
	public:
		AlgorithmRunnable(const QString& strSourceFile,
			const QString& strDestFile,
			ImageProcessor::ImageAlgorithm algorithm,
			QObject* pObserver)
			: m_strSourcePath(strSourceFile)
			, m_observer(pObserver)
			, m_strDestPath(strDestFile)
			, m_algorithm(algorithm)
		{
			m_strSourcePath = QUrl(strSourceFile).toLocalFile();
		}
		~AlgorithmRunnable(){}

		void run()
		{
			g_sFunction[m_algorithm](m_strSourcePath, m_strDestPath);
			QCoreApplication::postEvent(m_observer, new ExcuteEvent(this));
		}
	public:
		QPointer<QObject> m_observer;
		QString m_strSourcePath;
		QString m_strDestPath;
		ImageProcessor::ImageAlgorithm m_algorithm;
	};

	class ImageProcessorPrivate : QObject
	{
		friend class ImageProcessor;
	public:
		ImageProcessorPrivate(ImageProcessor* pProcessor)
			: m_pImageProcessor(pProcessor)
			, m_strTempPath(QDir::currentPath())
		{
 
		}

		~ImageProcessorPrivate()
		{

		}

		bool event(QEvent * e)
		{
			if (e->type() == ExcuteEvent::evType())
			{
				ExcuteEvent* ex = dynamic_cast<ExcuteEvent*>(e);
				if (m_runnerbles.contains(ex->runnableObj()))
				{
					m_notifiedAlgorithm = ex->runnableObj()->m_algorithm;
					m_strNotifiedSourceFile = ex->runnableObj()->m_strSourcePath;
					emit m_pImageProcessor->finished(ex->runnableObj()->m_strDestPath);
					m_runnerbles.removeOne(ex->runnableObj());
				}
				delete ex->runnableObj();
				return true;
			}

			return QObject::event(e);
		}

		void process(const QString& fileName, ImageProcessor::ImageAlgorithm algorithm)
		{
			QFileInfo fi(fileName);
			const QString& strDestFile = QString("%1/%2_%3").arg(m_strTempPath)
				.arg(algorithm).arg(fi.fileName());

			AlgorithmRunnable *r = new AlgorithmRunnable(fileName, strDestFile, algorithm, this);
			m_runnerbles << r;
			r->setAutoDelete(false);

			QThreadPool::globalInstance()->start(r);
		}

		void abort(const QString& fileName, ImageProcessor::ImageAlgorithm algorithm)
		{
			int size = m_runnerbles.size();
			AlgorithmRunnable* r;
			for (int i = 0; i < size; ++i)
			{
				r= m_runnerbles[i];
				if (r->m_strSourcePath == fileName && r->m_algorithm == algorithm)
				{
					m_runnerbles.removeAt(i);
					break;
				}
			}
		}
	private:
		ImageProcessor* m_pImageProcessor;
		QString			m_strTempPath;
		QList<AlgorithmRunnable*> m_runnerbles;
		QString m_strNotifiedSourceFile;
		ImageProcessor::ImageAlgorithm m_notifiedAlgorithm;

	};

	ImageProcessor::ImageProcessor(QObject* parent /*= NULL*/) 
		: m_d(new ImageProcessorPrivate(this))
	{
		
	}

	ImageProcessor::~ImageProcessor()
	{
		delete m_d;
	}

	QString ImageProcessor::sourceFile() const
	{
		return m_d->m_strNotifiedSourceFile;
	}

	ImageProcessor::ImageAlgorithm ImageProcessor::algorithm() const
	{
		return m_d->m_notifiedAlgorithm;
	}

	void ImageProcessor::process(const QString& fileName, ImageAlgorithm algorithm)
	{
		m_d->process(fileName, algorithm);
	}

	void ImageProcessor::abort(const QString& fileName, ImageAlgorithm algorithm)
	{
		m_d->abort(fileName, algorithm);
	}
}

