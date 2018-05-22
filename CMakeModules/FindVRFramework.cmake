function(VRFRAMEWORK_FIND_PATH module header)
   string(TOUPPER ${module} module_uc)

   # Try the user's environment request before anything else.
  find_path(${module_uc}_INCLUDE_DIR ${header}
    HINTS 
      ${VRFRAMEWORK_DIR}
    PATH_SUFFIXES 
      include 
      include/VRCore
      include/VRBase
      include/VRTools
    NO_DEFAULT_PATH
   )
endfunction()

function(VRFRAMEWORK_FIND_LIBRARY_PATH module_type module_library header)
  string(TOUPPER ${module_library} module_uc)

  # Try the user's environment request before anything else.
  find_path(VRFRAMEWORK_${module_type}_${module_uc}_INCLUDE_DIR ${header}
    HINTS 
      ${VRFRAMEWORK_DIR}
    PATH_SUFFIXES 
      include 
      include/VRCore/${module_library}
      include/VRBase/${module_library}
      include/VRTools/${module_library}
    NO_DEFAULT_PATH
   )
endfunction()

include(macro_find_package_handle_standard_args)

MACRO(VRFRAMEWORK_CHEKER module_type module_library)
  STRING(TOUPPER ${module_library} module_uc)
  SET(THIS_LIB_DEPEND_NAME ${module_type}_${module_uc})

  #验证变量合法
  find_package_handle_standard_args(
    ${THIS_LIB_DEPEND_NAME}

    VRFRAMEWORK_${module_type}_${module_uc}_LIBRARY
    VRFRAMEWORK_${module_type}_${module_uc}_LIBRARY_DEBUG
  )

  IF(NOT ${THIS_LIB_DEPEND_NAME}_FOUND)
    MESSAGE(FATAL_ERROR "--${THIS_LIB_DEPEND_NAME} not found")
  ENDIF()
ENDMACRO()

MACRO(VRFRAMEWORK_FIND_LIBRARY module_type module_library)
   string(TOUPPER ${module_library} module_uc)

   IF(NOT CMAKE_CL_64)
    find_library(VRFRAMEWORK_${module_type}_${module_uc}_LIBRARY
        NAMES 
            ${module_library}
        HINTS
            ${VRFRAMEWORK_DIR}
        PATH_SUFFIXES 
          lib
    )

    find_library(VRFRAMEWORK_${module_type}_${module_uc}_LIBRARY_DEBUG
        NAMES 
            ${module_library}d
        HINTS
            ${VRFRAMEWORK_DIR}
        PATH_SUFFIXES 
          lib
    )
  else()
    find_library(VRFRAMEWORK_${module_type}_${module_uc}_LIBRARY
          NAMES 
              ${module_library}
          HINTS
              ${VRFRAMEWORK_DIR}
          PATH_SUFFIXES 
            lib/x64
      )

    find_library(VRFRAMEWORK_${module_type}_${module_uc}_LIBRARY_DEBUG
          NAMES 
              ${module_library}d
          HINTS
              ${VRFRAMEWORK_DIR}
          PATH_SUFFIXES 
            lib/x64
    )
  endif()

  VRFRAMEWORK_CHEKER(${module_type} ${module_library})
endmacro()

MACRO(VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH module_type module_library include_header)
  VRFRAMEWORK_FIND_LIBRARY(${module_type} ${module_library})
  VRFRAMEWORK_FIND_LIBRARY_PATH(${module_type} ${module_library} ${include_header})
ENDMACRO()

#=======================================================
#VRFRAMEWORK_INCLUDE_DIR
VRFRAMEWORK_FIND_PATH(VRFRAMEWORK VRBase/glog/glog.h)

#========================VRBASE=========================
#VRFRAMEWORK_VRBASE_INCLUDE_DIR
VRFRAMEWORK_FIND_PATH(VRFRAMEWORK_VRBASE glog/glog.h)
#=============library==============
VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE BoostHelper uuid_helper.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE glog glog.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE jsoncpp json.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE OsgQtQuick OSGViewport.hpp)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE QtRibbon QtitanRibbon.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE QtTreePropertyBrowser qtvariantproperty.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE QtUtility QU_Macro.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE QtXMLObject QtXMLObject_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE QtXMLSerializer XmlStream.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRBASE UtilityKit UtilityKit_Export.h)
#========================VRCORE=========================
#VRFRAMEWORK_VRCORE_INCLUDE_DIR
VRFRAMEWORK_FIND_PATH(VRFRAMEWORK_VRCORE VRKernel/VRKernel_Macro.h)
#=============library==============
VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRCustomManipulator Projector.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRActors VRPlatActorProxy.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRDBEntities VRDBEntities_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRActorsUtil ActorObjectEx.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRAntenna VRAntenna_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRDevices VRAntennal.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VREffects VREffects_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRKernel exception_base.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRMainFrame mainwindow.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRPluginFace VRPluginFace_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRElevationCache Elevation_Def.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRPluginMsg Def_Macros.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRUtil VRUtil_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRWidgets VRWidgets_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRXMLSerializer Def_ActorType.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRModels VRModels_export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRRibbon QtitanDef.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRCORE VRPlatUI Def_VRPlatUI.h)
#========================VRCORE=========================
#VRFRAMEWORK_VRTOOLS_INCLUDE_DIR
VRFRAMEWORK_FIND_PATH(VRFRAMEWORK_VRTOOLS ReadAntenalLib/Antennal_Def.h)
#=============library==============
VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRTOOLS osgEphemeris Sphere.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRTOOLS PropagationModel PropagationModel_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRTOOLS PropagationCalc PropagationCalc_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRTOOLS ReadAntenalLib ReadAntennalLib_Export.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRTOOLS Interpolation Lagrange2.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRTOOLS OrbitTool cEci.h)

VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRTOOLS AntennalPreloadManager AntennalFile_Common.h)

OPTION(USE_CUDA_CALC "Use Cuda Libarary Calculation" OFF)
if(USE_CUDA_CALC)
  VRFRAMEWORK_FIND_INCLUDE_DIR_AND_LIBRARY_PATH(VRTOOLS VRCUDAKernel VRCUDAKernel_export.h)  
endif()
