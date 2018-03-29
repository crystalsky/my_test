#ifndef qt_includes_h__
#define qt_includes_h__

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#else
#define QStringLiteral QString::fromLocal8Bit
#include <QtGui/QMessageBox>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QDockWidget>
#include <QtGui/QListWidget>
#include <QtCore/QSettings>
#include <QtCore/QTextCodec>
#endif



#endif // qt_includes_h__
