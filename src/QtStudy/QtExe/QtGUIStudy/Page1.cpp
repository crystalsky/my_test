#include "Page1.h"
#include "QtProjectPath.h"
#include "QStyleSheetWidget1.h"
#include "controllerwindow.h"
#include "QFileDialog"
#include <QMediaPlayer>
#include "VideoWidget.h"
#include <QProcess>
#include <QMediaPlaylist>
#include <qt_windows.h>
#include <WinBase.h>
namespace Study_QtGui
{
	CPage1::CPage1( QWidget* pParnet )
		: QtUI::CStepBase(pParnet)
	{
		initFunctionWidgets();
	}

	CPage1::~CPage1()
	{

	}

	void CPage1::initFunctionWidgets()
	{
		addFunctionalWidget(QStringLiteral("测试窗体_1"), 
			new CWidget1(this));
	}

	Gui_Widget1::CQMLTranslucentWidget::CQMLTranslucentWidget()
	{
		setWindowFlags(
			Qt::FramelessWindowHint | 
			Qt::WindowMinimizeButtonHint |
			Qt::WindowSystemMenuHint);

		setAttribute(Qt::WA_TranslucentBackground);
	}

	void Gui_Widget1::CQMLTranslucentWidget::init()
	{

	}

	void Gui_Widget1::CQMLTranslucentWidget::paintEvent( QPaintEvent *ev )
	{
		//QWidget::paintEvent(ev);

		QPainter painter(this);
		painter.setPen(QPen(Qt::red, 2));
		painter.setBrush(Qt::yellow);
		painter.drawRect(0, 0, 100, 100);

	}
}

namespace Study_QtGui
{
	CWidget1::CWidget1( QWidget* pParent /*= NULL*/ ) : CButtonFunctionWidget(pParent)
	{
		init();
	}

	void CWidget1::init()
	{
		addFunctionButton(QStringLiteral("透明对话框测试"));
		addFunctionButton(QStringLiteral("MemoryTest"));
		addFunctionButton(QStringLiteral("MemoryTestVector"));
		addFunctionButton(QStringLiteral("QStyleSheet_Test"));
		addFunctionButton(QStringLiteral("视频播放"));
		addFunctionButton(QStringLiteral("运行程序"));
	}

	bool CWidget1::onButtonClicked( const QString& strFunctionButtonName )
	{
		if (strFunctionButtonName == QStringLiteral("透明对话框测试"))
		{
			static Gui_Widget1::CQMLTranslucentWidget* pWidget = 
				new Gui_Widget1::CQMLTranslucentWidget();

			pWidget->resize(400, 700);
			pWidget->show();
			pWidget->raise();

			return true;
		}
		else if (strFunctionButtonName == "MemoryTest")
		{
			static double *dval = NULL;
			if (dval == NULL)
			{
				dval = new double[100 * 1024 * 1024];
			}
			else
			{
				delete []dval;
				dval = NULL;
			}
		}
		else if (strFunctionButtonName == "MemoryTestVector")
		{
			/*static std::vector<double> vec;
			if (vec.empty())
			{
				vec.assign(100 * 1024 * 1024, 0);
			}
			else
			{
				//vec.clear();
				vec.swap(std::vector<double>());
			}*/

			static QVector<double> vec;
			if (vec.empty())
			{
				vec.resize(50 * 1024 * 1024);
			}
			else
			{
				vec.clear();
				//vec.swap(std::vector<double>());
			}
		}
		else if (strFunctionButtonName == "QStyleSheet_Test")
		{
			QStyleSheetWidget1* pWidget = new QStyleSheetWidget1();
			pWidget->resize(400, 700);
			pWidget->show();
			pWidget->raise();
		}
		else if (strFunctionButtonName == QStringLiteral("视频播放"))
		{
			QString path = QFileDialog::getOpenFileName(this , QString::fromLocal8Bit("播放视频文件"), QCoreApplication::applicationDirPath());

			if(path.count())
			{
				QMediaPlayer* player = new QMediaPlayer;

				QVideoWidget* pvideoWidget = new QVideoWidget;
				player->setVideoOutput(pvideoWidget);

				QMediaPlaylist *playlist = new QMediaPlaylist;
				playlist->addMedia(QUrl(path));
				playlist->setCurrentIndex(0);

				player->setPlaylist(playlist);
				pvideoWidget->show();
				player->play();
			}

			/*static VideoWidget* pWidget = NULL;
			if (pWidget == NULL)
			{
				pWidget = new VideoWidget();
			}

			QString path = QFileDialog::getOpenFileName(this , QString::fromLocal8Bit("播放视频文件"), QCoreApplication::applicationDirPath());
			if(path.count())
			{
				QFileInfo fileInfo(path);
				pWidget->showMaximized();
				pWidget->play(path);
			}*/
		}
		else if (strFunctionButtonName == QStringLiteral("运行程序"))
		{
			//F:\work_luli\_vire_projects\P_NetX\_my_branch\Bin\DLPlanner
			const QString strPath = "F:\\work_luli\\_vire_projects\\P_NetX\\_my_branch\\Bin\\DLPlanner";

			QProcess* prop1 = new QProcess(this);
			prop1->start(strPath + "\\DLPlanner2.bat");
			//int n = prop1->processId();
			/*QProcess *process = new QProcess(this);
			QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
			const QString s = strPath + "\\msys\\lib\\tcl8.4";
			env.insert("TCL_LIBRARY", s); // Add an environment variable
			const QString& strNewPath = strPath + "\\msys\\bin" + ";" +  env.value("Path");
			env.insert("Path", strNewPath);
			//process->setProcessEnvironment(env);

			process->start(strPath + "\\DLPlanner.exe");*/
		}

		return false;
	}
}