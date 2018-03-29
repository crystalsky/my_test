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
	void input(const QVector<double>& column , const QVector<double>& row , const QVector<double>& data);          //���ļ�����n*m�����ݵ�(x, y, z)
	double interp (double x , double y );    //ִ�ж�ԪLagrange��ֵ
	//void output ();         //�����ֵ��u,v���Ľ���ֵf���ļ�
	~Lagrange2 ();
};
#endif // Lagrange2_h__
