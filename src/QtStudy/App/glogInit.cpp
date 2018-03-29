#include "glogInit.h"
#include <QSettings>
#include <QApplication>
#include <QDir>
glogInit* glogInit::m_hInstance = NULL;

glogInit* glogInit::InitInstance()
{
	if(m_hInstance == NULL)
	{
		m_hInstance = new glogInit;
	}
	return m_hInstance;
}

glogInit* glogInit::GetInstance()
{
	if(m_hInstance == NULL)
	{
		m_hInstance = new glogInit;
	}
	return m_hInstance;
}

void glogInit::ExitInstance()
{
	if(m_hInstance)
	{
		delete m_hInstance;
		m_hInstance = NULL;
	}
}

glogInit::glogInit()
	: _bColorlogtostderr(true)
	, _nMax_log_size_MByte(10)
	, _bStop_logging_if_full_disk(true)
	, _nlogbufsecs(3)
	, _bInited(false)
{
	_readSetting();
}

glogInit::~glogInit()
{
	google::ShutdownGoogleLogging();
}

bool glogInit::_readSetting()
{
	return false;
}

bool glogInit::init( const char* arg )
{
	if (arg == NULL || _bInited)
	{
		return false;
	}

	google::InitGoogleLogging(arg);

#ifdef _DEBUG
	google::SetStderrLogging(google::GLOG_INFO); 
#else
	google::SetStderrLogging(google::GLOG_ERROR);
#endif
	
	//_logÎÄ¼þ¼Ð
	QDir dir;
	QString _logDir = QApplication::applicationDirPath() + "/" + "_log";
	if (!dir.exists(_logDir))
	{
		if(!dir.mkdir(_logDir))
		{
			_logDir = QApplication::applicationDirPath();
		}
	}

	const std::string strDir = _logDir.toLocal8Bit().data();

	google::SetLogDestination(google::GLOG_FATAL, std::string(strDir + "/" + "L_Fatal_").c_str());
	google::SetLogDestination(google::GLOG_ERROR, std::string(strDir + "/" + "L_Error_").c_str());
	google::SetLogDestination(google::GLOG_WARNING, std::string(strDir + "/" + "L_Warning_").c_str());
	google::SetLogDestination(google::GLOG_INFO, std::string(strDir + "/" + "L_Info_").c_str());

	FLAGS_logbufsecs = _nlogbufsecs; 
	FLAGS_colorlogtostderr = _bColorlogtostderr; 
	FLAGS_max_log_size = _nMax_log_size_MByte; 
	FLAGS_stop_logging_if_full_disk = _bStop_logging_if_full_disk; 

	google::SetLogFilenameExtension(".log");

	LOG(INFO) << "....!!google loging start!!....";

	_bInited = true;
	return true;
}

#define EXPECT_OP(op, val1, val2)                                       \
	do {                                                                  \
	if (!((val1) op (val2))) {                                          \
	fprintf(stderr, "Check failed: %s %s %s\n", #val1, #op, #val2);   \
	exit(1);                                                          \
	}                                                                   \
	} while (0)
#define EXPECT_EQ(val1, val2)  EXPECT_OP(==, val1, val2)
#define EXPECT_NE(val1, val2)  EXPECT_OP(!=, val1, val2)
#define EXPECT_GT(val1, val2)  EXPECT_OP(>, val1, val2)
#define EXPECT_LT(val1, val2)  EXPECT_OP(<, val1, val2)

void glogInit::_testGlog()
{
	LOG(INFO) <<"my first info";   int valueint=10;   
	LOG(WARNING) << "Wraldkfj";
	LOG(ERROR) << "12312321";
	int i = 4;
	LOG_IF(ERROR, i == 3) << "log_if i== 3 info";

	VLOG(-1) << "vlog -1";
	VLOG(0) << "vlog 0";
	VLOG(1) << "vlog 1";
	LOG(INFO) << "log info";
	LOG(WARNING) << "log warning";
	LOG(ERROR) << "log error";

	VLOG_IF(-1, true) << "vlog_if -1";
	VLOG_IF(-1, false) << "don't vlog_if -1";
	VLOG_IF(0, true) << "vlog_if 0";
	VLOG_IF(0, false) << "don't vlog_if 0";
	VLOG_IF(1, true) << "vlog_if 1";
	VLOG_IF(1, false) << "don't vlog_if 1";

	LOG_IF(INFO, false) << "don't log_if info";
	LOG_IF(WARNING, true) << "log_if warning";
	LOG_IF(WARNING, false) << "don't log_if warning";
	LOG_IF(ERROR, true) << "log_if error";
	LOG_IF(ERROR, false) << "don't log_if error";

	int c;
	c = 3; LOG_IF_EVERY_N(INFO, c -= 4, 1) << "log_if info every 1 expr";

	c = 3; LOG_IF_EVERY_N(ERROR, c -= 4, 1) << "log_if error every 1 expr";
	EXPECT_EQ(c, -1);
	c = 4; LOG_IF_EVERY_N(ERROR, c -= 4, 3) << "don't log_if info every 3 expr";
	EXPECT_EQ(c, 0);
	c = 4; LOG_IF_EVERY_N(ERROR, c -= 4, 3) << "don't log_if error every 3 expr";
	EXPECT_EQ(c, 0);
	c = 5; VLOG_IF_EVERY_N(0, c -= 4, 1) << "vlog_if 0 every 1 expr";
	EXPECT_EQ(c, 1);
	c = 5; VLOG_IF_EVERY_N(100, c -= 4, 3) << "vlog_if 100 every 3 expr";
	EXPECT_EQ(c, 1);
	c = 6; VLOG_IF_EVERY_N(0, c -= 6, 1) << "don't vlog_if 0 every 1 expr";
	EXPECT_EQ(c, 0);
	c = 6; VLOG_IF_EVERY_N(100, c -= 6, 3) << "don't vlog_if 100 every 1 expr";
	EXPECT_EQ(c, 0);
}
