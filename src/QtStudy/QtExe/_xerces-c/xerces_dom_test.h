#ifndef xerces_dom_test_h__
#define xerces_dom_test_h__
#include "QtProjectPath.h"
#include "Base.h"
#include "xercesc\util\Xerces_autoconf_config.hpp"

class xerces_dom_test : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(xerces_dom_test)
public:
	xerces_dom_test();
	~xerces_dom_test();

public:
	virtual void run();
protected:
	bool read_with_chinese();
	bool write_with_chinese();
public:
	static std::string getString(const XMLCh *pch);
};

#ifndef XERCES_STRING
#define XERCES_STRING(s)\
	xerces_dom_test::getString(s);
#endif
#endif // xerces_dom_test_h__
