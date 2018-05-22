###############################################################################
# CMake module to search for VC100 library
#
#  @Copyright: Copyright (c) 2012
#  @Company: 深圳置辰海信科技有限公司
#  @WebSite: http://www.zhichenhaixin.com/
#  @author 李鹭
#  
#  @Revision History
#  
#  <pre>
#  &lt;Date&gt;, &lt;Who&gt;, &lt;What&gt;
#  &#064;2012-09-27, 李鹭, Initial.
# 
###############################################################################
SET(VC100_HOME $ENV{ZCHX_3RDPARTY_PATH}/vc100)


INSTALL(FILES 
    ${VC100_HOME}/msvcp100.dll
    ${VC100_HOME}/msvcr100.dll
    DESTINATION bin
)
    
