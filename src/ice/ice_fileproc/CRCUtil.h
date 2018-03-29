#ifndef CRCUtil_h__
#define CRCUtil_h__

#include <string>
#include <vector>
#include <map>
#include <list>

namespace CRCUtil
{
	//一次性验证CRC处理
	unsigned int crc32_UseStaticTable( const char *buf, unsigned int size);

	///*第一次传入的值需要固定,如果发送端使用该值计算crc校验码, 
	///那么接收端也同样需要使用该值进行计算*/ 
	static unsigned int g_nCRCFirstVal = 0xFFFFFFFF;

	/******************************************************************
	 * @fn crc32_UseStaticTable
	 * @brief 增量法计算CRC，主要用于大文件校验用
	 * @param[in] unsigned int crc:首次调用用默认的 g_nCRCFirstVal值（也不一定需要这这个值）
	 * @param[in] const unsigned char * buf:要校验的数据
	 * @param[in] unsigned int size: 数据大小
	 * @exception no
	 * @return unsigned int : crc32码
	 * @pre 
	 * @see 
	 *******************************************************************/
	unsigned int crc32_UseStaticTable(unsigned int crc, const char *buf, unsigned int size);
}



#endif // CRCUtil_h__
