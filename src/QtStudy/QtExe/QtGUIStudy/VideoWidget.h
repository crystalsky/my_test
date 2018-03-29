//************************************************************************/
//********************---------------------------------*******************/
//*******************|    Copyright (c) 2003 - 2014    |******************/
//*******************|      by ViRe Technologies.      |******************/
//*******************|       All Rights Reserved       |******************/
//********************---------------------------------*******************/
//************************************************************************/
//
// If any question, please write to VIRE Technologies for 
// more information: 
//			Room 1222,High Tech Mansion of BUPT, 
//			Beijing, China
//			Post Code: 100876.
// 
// For more, please visit company website: www.vi-re.com
//************************************************************************/
/************************************************************************* 
 * @file     : VideoWidget.h
 * @brief    : 
 * @note     : 
 * @author   : dell
 * @date     : 2015/01/19
 * @version  : 1.0.0.0
 * @CopyRight: 
 *************************************************************************/
#pragma once

#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlayer>
#include <QMainWindow>

class VideoWidget : public QMainWindow
{
	Q_OBJECT
public:
	VideoWidget(QWidget *parent = 0);
	bool isPaused();
	void play(const QString& path);

signals:
	void finished();

public slots:
	void slotStateChanged(QMediaPlayer::State);
	void pause();
	void play();
	void stop();

private:
	QVideoWidget* m_pVideoWidget;
	QMediaPlayer* m_player;
};