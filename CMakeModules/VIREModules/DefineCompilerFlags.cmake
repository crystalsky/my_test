###############################################################################
# �������ѡ��
#
# 
# /DWIN32 : 
# /D_WINDOWS 
# /D_DEBUG
# /D NDEBUG
#
# /W  ���þ���ȼ�:/W3�Ǿ��漶��Ϊ3   /W0   �������о���
# /Zm ���ñ��������ڴ��������  /Zm1500  ���ñ��������ڴ��������Ϊ1000M
# /EH   ָ���쳣����ģ�� 
# /EHs  ����ͬ�� C++ �쳣����  enable synchronous C++ EH 
# /EHc  extern��C��Ĭ��Ϊ nothrow  extern "C" defaults to nothrow 
# /MD   ʹ��   MSVCRT.lib   �����Դ������߳�   DLL    
# /MDd   ʹ��   MSVCRTD.lib   �����Դ������Զ��߳�   DLL   
# /GR[-]  ���� C++ RTTI  enable C++ RTTI 
#
# /O1   ����С����    
# /O2   �������ٴ���    
# /Oa   ����û�б���    
# /Ob0  ��������չ��    /Ob1 Only __inline  /Ob2  Any Suitable
# /Od   �����Ż�    
# /Og   ʹ��ȫ���Ż�    
# /Oi   �����ڲ�����    
# /Op   ���Ƹ�����һ����    
# /Os   �����С����    
# /Ot   �����ٶ�����    
# /Ow   �ٶ��ں���������ʹ�ñ���    
# /Ox   ʹ������Ż�   (/Ob1gity   /Gs)    
# /Oy   ʡ�Կ��ָ��  
#
# /RTC   ��������ʱ������   
# /Zi   ���������ĵ�����Ϣ         

# 
###############################################################################
IF(MSVC)   

	SET(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR")
	SET(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")
	SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MD /O1 /Ob1 /D NDEBUG")
	SET(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /D NDEBUG")
	SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /Ob0 /Od")


ENDIF()   
