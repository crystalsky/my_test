#include "Lagrange2.h"
#include "string.h"

Lagrange2::Lagrange2(int columnCount, int rowCount)
{
	int k;
	m_columnCount = columnCount;  m_rowCount = rowCount;
	x = new double[m_columnCount]; //¶¯Ì¬·ÖÅäÄÚ´æ
	y = new double[m_rowCount];
	m_data = new double*[m_columnCount];
	for (k=0; k<m_columnCount; k++) { m_data[k] = new double[m_rowCount]; }
}

Lagrange2::~Lagrange2()
{
	int i;
	for (i=0; i<m_columnCount; i++) { delete [] m_data[i]; }
	delete [] m_data;
	delete [] x, y;  
}

void Lagrange2::input( const QVector<double>& column , const QVector<double>& row , const QVector<double>& data )
{
	int colCount = column.count() > m_columnCount ? m_columnCount : column.count();
	int rowCount = row.count() > m_rowCount ? m_rowCount : row.count();
	memcpy(x , column.data() , sizeof(double) * colCount);
	memcpy(y , row.data() , sizeof(double) * rowCount);
	int dataCount = colCount * rowCount;
	dataCount = data.count() > dataCount ? dataCount : data.count();

	const double* temDatap = data.data();
	for (int row = 0 ; row < m_rowCount ; row++)
	{
		for (int column = 0 ; column < m_columnCount ; column++ , temDatap++)
		{
			m_data[column][row] = *temDatap;
		}
	}
}

double Lagrange2::interp( double uu , double vv )
{
	int ip,ipp,i,j,kk,iq,iqq,k;
	double h,b[10];
	u = uu;  v = vv;
	if (u<=x[0]) { ip=1; ipp=4;}
	else if (u>=x[m_columnCount-1]) { ip=m_columnCount-3; ipp=m_columnCount;}
	else
	{ 
		i=1; j=m_columnCount;
		while (((i-j)!=1)&&((i-j)!=-1))
		{ 
			kk=(i+j)/2;
			if (u<x[kk-1]) j=kk;
			else i=kk;
		}
		ip=i-3; ipp=i+4;
	}
	if (ip<1) ip=1;
	if (ipp>m_columnCount) ipp=m_columnCount;
	if (v<=y[0]) { iq=1; iqq=4;}
	else if (v>=y[m_rowCount-1]) { iq=m_rowCount-3; iqq=m_rowCount;}
	else
	{ 
		i=1; j=m_rowCount;
		while (((i-j)!=1)&&((i-j)!=-1))
		{ 
			kk=(i+j)/2;
			if (v<y[kk-1]) j=kk;
			else i=kk;
		}
		iq=i-3; iqq=i+4;
	}
	if (iq<1) iq=1;
	if (iqq>m_rowCount) iqq=m_rowCount;
	for (i=ip-1;i<=ipp-1;i++)
	{ 
		b[i-ip+1]=0.0;
		for (j=iq-1;j<=iqq-1;j++)
		{ 
			h=m_data[i][j];
			for (k=iq-1;k<=iqq-1;k++)
				if (k!=j) h=h*(v-y[k])/(y[j]-y[k]);
			b[i-ip+1]=b[i-ip+1]+h;
		}
	}
	f=0.0;
	for (i=ip-1;i<=ipp-1;i++)
	{ 
		h=b[i-ip+1];
		for (j=ip-1;j<=ipp-1;j++)
			if (j!=i) h=h*(u-x[j])/(x[i]-x[j]);
		f=f+h;
	}
	return f;

}

