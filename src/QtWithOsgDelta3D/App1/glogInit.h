#ifndef glogInit_h__
#define glogInit_h__

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "glog.h"

class glogInit
{
public:
	static glogInit* InitInstance();
	static void ExitInstance();
	static glogInit* GetInstance();
protected:
	static glogInit* m_hInstance; 

	glogInit();
	~glogInit();
public:
	bool init(const char* arg);

protected:
	bool _readSetting();

	void _testGlog();
private:
	bool _bColorlogtostderr;	//控制台是否以不同颜色输出
	int	 _nMax_log_size_MByte;		//最大字节数以MByte
	bool _bStop_logging_if_full_disk;	//磁盘满后停止日志
	int	 _nlogbufsecs; //刷新Log最大时间(s)
	bool _bInited;	//是否初始化过
};

#endif // glogInit_h__
