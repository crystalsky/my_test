#ifndef T04_h__
#define T04_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include "CFunctionOSGViewerWidget.h"
#include "ReflectObject.h"
#include "OSGBaseDef.h"

namespace OSG_ProgramingGuid{

class T04 : public CFunctionOSGViewerWidget
{
public:
	T04(QWidget* pParnet = NULL);
	~T04();

protected:
	void slotButtonClicked(const QString& strFunctionButtonName);

	
protected:

private:

};

}

#endif // T04_h__
