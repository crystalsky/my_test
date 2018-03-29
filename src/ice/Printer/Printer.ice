
[["cpp:include:Ice/Identity.h"]]
#include "Ice/Identity.ice"

module Demo
{
    interface PrinterCallBack
    {
        void setID(string s);
    };

    interface Printer
    {
        void printString(string s);
        void addClient(PrinterCallBack* pxy);
    };

    
};

