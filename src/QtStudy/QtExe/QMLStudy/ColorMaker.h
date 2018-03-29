#ifndef ColorMaker_h__
#define ColorMaker_h__

#include "QMLStudyBase.h"

#define USE_CPP_OBJECT_TO_QMLGLOBEPROPERTY

namespace Study_QML
{
	class ColorMaker : public QObject
	{
		Q_OBJECT
		Q_ENUMS(GenerateAlgorithm)
		Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
		Q_PROPERTY(QColor timeColor READ timeColor)

	Q_SIGNALS:
		void colorChanged(const QColor& color);
		void currentTime(const QString& strTime);

	public Q_SLOTS:
		void start();
		void stop();
	public:
		ColorMaker(QObject* parent = NULL);
		~ColorMaker();

		enum GenerateAlgorithm
		{
			RandomRGB,
			RandomGreen,
			RandomRed,
			RandomBlue,
			LinearIncrease
		};

		QColor color()const;
		void setColor(const QColor& color);
		QColor timeColor()const;

		Q_INVOKABLE GenerateAlgorithm algorithm()const;
		Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm);

	protected:
		void timerEvent(QTimerEvent *e);

	private:
		QColor	m_curColor;
		GenerateAlgorithm m_algorithm;
		int		m_nColorTimer;
	};

	class ColorMakerWidget : public QtUI::CWidgetBase
	{
		Q_OBJECT
	public:
		ColorMakerWidget(QWidget* pParent = NULL);
		~ColorMakerWidget();

		virtual void refresh();

	private:
		QWidget*	m_pQuitWidget;
		QVBoxLayout* m_pLay;
	};
}

#endif // ColorMaker_h__
