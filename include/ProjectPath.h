#ifndef ProjectPath_h__
#define ProjectPath_h__

#include <FileFunc.h>
#include <sstream>

namespace DirPaths
{
	static std::string GetAppRootDataPath()
	{
		const std::string str = UtilityKit::FileFunc::GetApplicationFileDir()  + "..\\..\\data";
		return str;
	}

	static std::string GetIceConfigPath(const std::string& strConfigName)
	{
		static std::stringstream stream;
		stream.clear();
		stream << GetAppRootDataPath() << "\\" 
			<< "ice" << "\\"
			<< strConfigName;
		return stream.str();
	}

	static std::string GetOSGDataPath()
	{
		const std::string str = GetAppRootDataPath() + "/" + "osgdata/";
		return str;
	}
}


#endif // ProjectPath_h__