#include "DQ.h"

DQ::DQ(QObject* parent)
	: QObject(parent)
{
	
}

DQ::~DQ()
{
	
}

namespace Qn
{

	DQ1::DQ1(QObject* parent)
		: QObject(parent)
	{

	}

	DQ1::~DQ1()
	{

	}
}


class DQPrivate : public QObject
{
	Q_OBJECT
Q_SIGNALS:
	//пе╨е


public:
	DQPrivate(QObject* parent = NULL);
	~DQPrivate();

public:

	protected slots:

protected:

private:

};

#include "DQ.moc"
