#===================================================================
MACRO(_SET_OSG_OSGEARTH_DELTA3D_DIR)
    SET_DEPENDS_DIR(OSG             "${THIRD_PART_ROOT}/OSG(3.2.1)")
    SET_DEPENDS_DIR(DELTA3D         "${THIRD_PART_ROOT}/DELTA3D(OSG3.2.1)")
    SET_DEPENDS_DIR(OSGEARTH        "${THIRD_PART_ROOT}/OSGEARTH(OSG3.2.1)")
    #Openthreads
    SET_DEPENDS_DIR(OPENTHREADS     "$ENV{OSG_ROOT}")
    
    SET_DEPENDS_DIR(CURL            "$ENV{OSG_ROOT}/ext")
    
    #Delta3d相关依赖库目录指定
    SET_DEPENDS_DIR(ODE         "$ENV{DELTA3D_ROOT}/ext")
    #SET_DEPENDS_DIR(XERCESC     "$ENV{DELTA3D_ROOT}/ext")
    SET_DEPENDS_DIR(CAL3D       "$ENV{DELTA3D_ROOT}/ext")
    SET_DEPENDS_DIR(OPENALDIR   "$ENV{DELTA3D_ROOT}/ext")
    SET_DEPENDS_DIR(CEGUI       "$ENV{DELTA3D_ROOT}/ext")
    SET_DEPENDS_DIR(CPPUNIT     "$ENV{DELTA3D_ROOT}/ext")
    SET_DEPENDS_DIR(GDAL        "$ENV{DELTA3D_ROOT}/ext")
    SET_DEPENDS_DIR(PLIB        "$ENV{DELTA3D_ROOT}/ext")
    SET_DEPENDS_DIR(DIS         "$ENV{DELTA3D_ROOT}/ext")
    SET_DEPENDS_DIR(ZLIB        "$ENV{DELTA3D_ROOT}/ext")
	SET_DEPENDS_DIR(ALUT        "$ENV{DELTA3D_ROOT}/ext")
	SET_DEPENDS_DIR(PAL         "$ENV{DELTA3D_ROOT}/ext")
ENDMACRO()

#===================================================================
#三方库子目录确定
MACRO(_SET_OTHER_DEPENDS_DIR path)
    #===================================================================
    #SET_DEPENDS_DIR(OSG             "${THIRD_PART_ROOT}/OSG(3.2.1)")
    
    #QtRibbon
    #SET_DEPENDS_DIR(QTRIBBON        "${THIRD_PART_ROOT}/QtRibbon")

    #UtilityKit
    #SET_DEPENDS_DIR(UTILITYKIT      "${THIRD_PART_ROOT}/UtilityKit")

    #QtUtility
    #SET_DEPENDS_DIR(QTUTILITY       "${THIRD_PART_ROOT}/QtUtility")

    #tinyxml
    #SET_DEPENDS_DIR(TINYXML         "${THIRD_PART_ROOT}/tinyxml")

    #ChartDirector
    #SET_DEPENDS_DIR(CHARTDIRECTOR   "${THIRD_PART_ROOT}/ChartDirector")
    
    #Glog
    #SET_DEPENDS_DIR(GLOG            "${THIRD_PART_ROOT}/glog")
    
    #QtXMLSerializer
    #SET_DEPENDS_DIR(QTXMLSERIALIZER "${THIRD_PART_ROOT}/QtXMLSerializer")

    #QTUI
    #SET_DEPENDS_DIR(QTUI              "${THIRD_PART_ROOT}/QtUI")
    
    #PLOTLAB
    #SET_DEPENDS_DIR(PLOTLAB         "${THIRD_PART_ROOT}/PlotLab")
    
    #QtTreePropertyBrowser
    #SET_DEPENDS_DIR(QTTREEPROPERTYBROWSER "${THIRD_PART_ROOT}/QtTreePropertyBrowser")

    #ICE
    #SET_DEPENDS_DIR(ICE             "${THIRD_PART_ROOT}/Ice-3.5.1")

    #qwtpolar
    #SET_DEPENDS_DIR(QWTPOLAR        "${THIRD_PART_ROOT}/qwtpolar")

    #qwtplot3d
    #SET_DEPENDS_DIR(QWTPLOT3D       "${THIRD_PART_ROOT}/qwtplot3d")

    #qwt
    #SET_DEPENDS_DIR(QWT             "${THIRD_PART_ROOT}/qwt6.0")

    #DDST
    #SET_DEPENDS_DIR(DDST            "${THIRD_PART_ROOT}/ddst")
    #===================================================================
    SET_DEPENDS_DIR(FREEGLUT        "${path}/freeglut-2.0.0")
    SET_DEPENDS_DIR(GLEW            "${path}/glew-2.1.0")
    SET_DEPENDS_DIR(GLFW            "${path}/glfw-3.2.1")
    SET_DEPENDS_DIR(GLAD            "${path}/glad")
    SET_DEPENDS_DIR(GLTOOLS          "${path}/GLtools")
    #===================================================================
ENDMACRO()
#===================================================================


MACRO(THIRD_PART_SET path)
    #_SET_OSG_OSGEARTH_DELTA3D_DIR()

    _SET_OTHER_DEPENDS_DIR(${path})
ENDMACRO()


