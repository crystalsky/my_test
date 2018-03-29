#ifndef QtProjectPath_h__
#define QtProjectPath_h__

#include <QApplication>
#include <QString>

namespace QtProjectPath
{
	namespace DirPaths
	{
		static QString GetAppRootDataPath()
		{
			const QString strData= QApplication::applicationDirPath() + "/" + "../../data";
			return strData;
		}

		static QString GetQMLPath()
		{
			const QString strData= GetAppRootDataPath() + "/" + "QML";
			return strData;
		}
	}

	namespace FilePath
	{
		static QString GetQMLFilePath(const QString& fileName)
		{
			const QString strData = DirPaths::GetQMLPath() + "/" + fileName;
			return strData;
		}
	}
}

#endif // QtProjectPath_h__