#ifndef Lagrange2_h__
#define Lagrange2_h__
//#include "Tool/Interpolation/export.h"
#include <QVector>

class  Lagrange2
{
private: 
	int m_columnCount, m_rowCount;
	double  *x, *y, **m_data, u, v, f;
public:
	Lagrange2 (int columnCount, int rowCount);
	void input(const QVector<double>& column , const QVector<double>& row , const QVector<double>& data);          //由文件读入n*m个数据点(x, y, z)
	double interp (double x , double y );    //执行二元Lagrange插值
	//void output ();         //输出插值点u,v处的近似值f到文件
	~Lagrange2 ();
};
#endif // Lagrange2_h__
