#include "ColorMaker.h"
#include <QDateTime>
#include "qqml.h"
#include <QQmlContext>

namespace Study_QML
{
	ColorMaker::ColorMaker(QObject* parent /*= NULL*/)
	{
		m_algorithm = RandomRGB;
		m_curColor = Qt::black;
		m_nColorTimer = 0;
	}

	ColorMaker::~ColorMaker()
	{

	}

	QColor ColorMaker::color() const
	{
		return m_curColor;
	}

	void ColorMaker::setColor(const QColor& color)
	{
		m_curColor = color;
		emit colorChanged(color);
	}

	QColor ColorMaker::timeColor() const
	{
		QTime t = QTime::currentTime();
		return QColor::fromRgb(t.hour(), t.minute() * 2, t.second() * 4);
	}

	ColorMaker::GenerateAlgorithm ColorMaker::algorithm() const
	{
		return m_algorithm;
	}

	void ColorMaker::setAlgorithm(ColorMaker::GenerateAlgorithm algorithm)
	{
		m_algorithm = algorithm;
	}

	void ColorMaker::timerEvent(QTimerEvent *e)
	{
		if (e->timerId() == m_nColorTimer)
		{
			switch (m_algorithm)
			{
			case RandomRGB:
			{
				m_curColor.setRgb(qrand() % 255, qrand() % 255,
					qrand() % 255);
			}
			break;

			case RandomRed:
			{
				m_curColor.setRed(qrand() % 255);
			}
			break;

			case RandomGreen:
			{
				m_curColor.setGreen(qrand() % 255);
			}
			break;

			case RandomBlue:
			{
				m_curColor.setBlue(qrand() % 255);
			}
			break;

			case LinearIncrease:
			{
				m_curColor.setRgb(
				m_curColor.red() + 10,
				m_curColor.green() + 14,
				m_curColor.blue() + 18);
			}
			break;

			default:
			{

			}
			break;
			}

			emit colorChanged(m_curColor);
			emit currentTime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
		}
		else
		{
			QObject::timerEvent(e);
		}
		
	}

	void ColorMaker::start()
	{
		if (m_nColorTimer == 0)
		{
			m_nColorTimer = startTimer(200);
		}
	}

	void ColorMaker::stop()
	{
		if (m_nColorTimer > 0)
		{
			killTimer(m_nColorTimer);
			m_nColorTimer = 0;
		}
	}
}

namespace Study_QML
{
	ColorMakerWidget::ColorMakerWidget(QWidget* pParent)
		: QtUI::CWidgetBase(pParent)
		, m_pQuitWidget(NULL)
	{
		m_pLay = new QVBoxLayout;
		setLayout(m_pLay);

		refresh();
	}

	ColorMakerWidget::~ColorMakerWidget()
	{

	}

	void ColorMakerWidget::refresh()
	{
		if (m_pQuitWidget)
		{
			m_pQuitWidget->close();
		}

		QQuickView *m_pView = new QQuickView();
		

#ifndef USE_CPP_OBJECT_TO_QMLGLOBEPROPERTY
		const QString& strFile = QtProjectPath::FilePath::GetQMLFilePath("ColorMakerTest.qml");
		qmlRegisterType<ColorMaker>("example.qt.ColorMaker", 1, 0, "ColorMaker");
#else
		const QString& strFile = QtProjectPath::FilePath::GetQMLFilePath("ColorMakerTest2.qml");
		m_pView->rootContext()->setContextProperty("colorMaker", new ColorMaker());
#endif
		m_pView->setSource(QUrl::fromLocalFile(strFile));

		m_pQuitWidget = QWidget::createWindowContainer(m_pView, this);
		m_pQuitWidget->setAttribute(Qt::WA_DeleteOnClose);

		m_pLay->addWidget(m_pQuitWidget);
	}
}