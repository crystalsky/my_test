#ifndef PrinterCallBackI_h__
#define PrinterCallBackI_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <Printer.h>

class PrinterCallBackI : public Demo::PrinterCallBack
{
public:
	PrinterCallBackI();
	~PrinterCallBackI();

public:
	 virtual void setID(const ::std::string& id, const ::Ice::Current& = ::Ice::Current())
	 {
		 std::cout << id << std::endl;
	 }
protected:
	
private:

};

#endif // PrinterCallBackI_h__
