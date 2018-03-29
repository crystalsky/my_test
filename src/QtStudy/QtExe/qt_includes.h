#ifndef qt_includes_h__
#define qt_includes_h__

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#else
#include <QtGui/QMessageBox>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QDockWidget>
#include <QtGui/QListWidget>
#include <QtCore/QSettings>
#include <QtCore/QTextCodec>
#endif


#endif // qt_includes_h__
