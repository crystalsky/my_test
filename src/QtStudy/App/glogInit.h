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
	bool _bColorlogtostderr;	//����̨�Ƿ��Բ�ͬ��ɫ���
	int	 _nMax_log_size_MByte;		//����ֽ�����MByte
	bool _bStop_logging_if_full_disk;	//��������ֹͣ��־
	int	 _nlogbufsecs; //ˢ��Log���ʱ��(s)
	bool _bInited;	//�Ƿ��ʼ����
};

#endif // glogInit_h__
