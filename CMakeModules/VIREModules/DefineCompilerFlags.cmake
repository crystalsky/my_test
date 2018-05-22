###############################################################################
# 定义编译选项
#
# 
# /DWIN32 : 
# /D_WINDOWS 
# /D_DEBUG
# /D NDEBUG
#
# /W  设置警告等级:/W3是警告级别为3   /W0   禁用所有警告
# /Zm 设置编译器的内存分配限制  /Zm1500  设置编译器的内存分配限制为1000M
# /EH   指定异常处理模型 
# /EHs  启用同步 C++ 异常处理  enable synchronous C++ EH 
# /EHc  extern“C”默认为 nothrow  extern "C" defaults to nothrow 
# /MD   使用   MSVCRT.lib   编译以创建多线程   DLL    
# /MDd   使用   MSVCRTD.lib   编译以创建调试多线程   DLL   
# /GR[-]  启用 C++ RTTI  enable C++ RTTI 
#
# /O1   创建小代码    
# /O2   创建快速代码    
# /Oa   假设没有别名    
# /Ob0  控制内联展开    /Ob1 Only __inline  /Ob2  Any Suitable
# /Od   禁用优化    
# /Og   使用全局优化    
# /Oi   生成内部函数    
# /Op   改善浮点数一致性    
# /Os   代码大小优先    
# /Ot   代码速度优先    
# /Ow   假定在函数调用中使用别名    
# /Ox   使用最大优化   (/Ob1gity   /Gs)    
# /Oy   省略框架指针  
#
# /RTC   启用运行时错误检查   
# /Zi   生成完整的调试信息         

# 
###############################################################################
IF(MSVC)   

	SET(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR")
	SET(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")
	SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MD /O1 /Ob1 /D NDEBUG")
	SET(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /D NDEBUG")
	SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /Ob0 /Od")


ENDIF()   
