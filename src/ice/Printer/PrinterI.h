#ifndef PrinterI_h__
#define PrinterI_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "Printer.h"
#include <ice/Connection.h>

class PrinterI : public Demo::Printer
{
public:
	virtual void printString(const std::string& s, const Ice::Current&)
	{
		std::cout << s << std::endl;
	}

	virtual void addClient(const ::Demo::PrinterCallBackPrx& pxy, const ::Ice::Current& current)
	{
		pxy->setID("adfb");
	}
};


#endif // PrinterI_h__
