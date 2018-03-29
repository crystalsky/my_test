#ifndef FileTransferTask_h__
#define FileTransferTask_h__
#include "UserTask.h"
#include <istream>
class FileTransferTask : public UserTask
{
public:
	FileTransferTask(const Login::LoginCallBackPrx& pxyClient);
	~FileTransferTask();

public:
	virtual bool initialTaskAditionalInfo(const DataTransmitter::ArrayData& jsonArrayData);

	//process data
	virtual bool onRecvData(const DataTransmitter::SendDataPackagePtr& data);
	virtual bool isHasFinishedRecvData()const;
	virtual bool onFinish();
protected:
	
private:
	boost::shared_ptr<std::fstream>	_fileWirter;
};

#endif // FileTransferTask_h__
