#ifndef boost_pool_h__
#define boost_pool_h__

#include "Base.h"
#include <boost/pool/pool.hpp>
#include <QList>

typedef struct my
{
	double *m_pValue;
	double *m_pLatLong;
	int nRowCount;
	int nColumeCount;

public:
	my()
	{
		m_pValue = 0;
		m_pLatLong = 0;
		nRowCount = 0;
		nColumeCount = 0;
	}
};

class boost_pool : public my_kit::base
{
	DECLARE_REFLECTED_CLASS(boost_pool)
public:
	boost_pool();
	~boost_pool();

public:
	virtual void run();
protected:
	
private:
	static boost::pool<> pdouble;

	QList<my> mListMy;
};



#endif // boost_pool_h__
