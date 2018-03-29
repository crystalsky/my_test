#include "VideoWidget.h"
#include <QUrl>

VideoWidget::VideoWidget( QWidget *parent /*= 0*/ ): QMainWindow( parent)
{
	m_pVideoWidget = new QVideoWidget(this);
	setCentralWidget(m_pVideoWidget);

	m_player = new QMediaPlayer(this);
	m_player->setVideoOutput(m_pVideoWidget);
	connect(m_player , SIGNAL(stateChanged(QMediaPlayer::State)) , SLOT(slotStateChanged( QMediaPlayer::State )));
}

void VideoWidget::slotStateChanged( QMediaPlayer::State state)
{
	switch (state)
	{
	case QMediaPlayer::StoppedState:
		emit finished();
		break;
	}
}

void VideoWidget::pause()
{
	m_player->pause();
}

void VideoWidget::play()
{
	m_player->play();
}

void VideoWidget::play( const QString& path )
{
	const QUrl playURL(path);
	m_player->setMedia(QMediaContent(playURL));
	play();
}

bool VideoWidget::isPaused()
{
	return m_player->state() == QMediaPlayer::PausedState;
}

void VideoWidget::stop()
{
	m_player->stop();
}
