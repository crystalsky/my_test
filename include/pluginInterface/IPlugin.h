#ifndef IPlugin_h__
#define IPlugin_h__

#include <assert.h>
#include <iostream>

class IMain;

class IPlugin
{
public:
	IPlugin(){m_pMain = NULL;}
	virtual ~IPlugin(){}

public:
	void setIMain(IMain* pMain)
	{
		assert(pMain != NULL);
		m_pMain = pMain;
	}
	IMain*	getMain(){return m_pMain;}
public:
	virtual bool create()
	{
		std::cout << "IPlugin create nothing...." << std::endl;
	}
	virtual bool destroy()
	{
		std::cout << "IPlugin destroy nothing...." << std::endl;
	}
private:
	IMain*	m_pMain;
};

#endif // IPlugin_h__
