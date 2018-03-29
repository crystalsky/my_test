#ifndef CRCUtil_h__
#define CRCUtil_h__

#include <string>
#include <vector>
#include <map>
#include <list>

namespace CRCUtil
{
	//һ������֤CRC����
	unsigned int crc32_UseStaticTable( const char *buf, unsigned int size);

	///*��һ�δ����ֵ��Ҫ�̶�,������Ͷ�ʹ�ø�ֵ����crcУ����, 
	///��ô���ն�Ҳͬ����Ҫʹ�ø�ֵ���м���*/ 
	static unsigned int g_nCRCFirstVal = 0xFFFFFFFF;

	/******************************************************************
	 * @fn crc32_UseStaticTable
	 * @brief ����������CRC����Ҫ���ڴ��ļ�У����
	 * @param[in] unsigned int crc:�״ε�����Ĭ�ϵ� g_nCRCFirstValֵ��Ҳ��һ����Ҫ�����ֵ��
	 * @param[in] const unsigned char * buf:ҪУ�������
	 * @param[in] unsigned int size: ���ݴ�С
	 * @exception no
	 * @return unsigned int : crc32��
	 * @pre 
	 * @see 
	 *******************************************************************/
	unsigned int crc32_UseStaticTable(unsigned int crc, const char *buf, unsigned int size);
}



#endif // CRCUtil_h__
