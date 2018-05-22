# This module defines

# OSG_LIBRARY
# OSG_FOUND, if false, do not try to link to osg
# OSG_INCLUDE_DIRS, where to find the headers
# OSG_INCLUDE_DIR, where to find the source headers
# OSG_GEN_INCLUDE_DIR, where to find the generated headers

# to use this module, set variables to point to the osg build
# directory, and source directory, respectively
# OSGDIR or OSG_SOURCE_DIR: osg source directory, typically OpenSceneGraph
# OSG_DIR or OSG_BUILD_DIR: osg build directory, place in which you've
#    built osg via cmake 

# Header files are presumed to be included like
# #include <osg/PositionAttitudeTransform>
# #include <osgUtil/SceneView>



include(${THIS_MODULE_PATH}/find_module/osg/FindOpenThreads.cmake)

include(${THIS_MODULE_PATH}/find_module/osg/Findosg.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgAnimation.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgDB.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgFX.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgGA.cmake)
#include(${THIS_MODULE_PATH}/find_module/osg/FindosgIntrospection.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgManipulator.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgParticle.cmake)
#include(${THIS_MODULE_PATH}/find_module/osg/FindosgProducer.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgShadow.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgSim.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgTerrain.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgText.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgUtil.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgViewer.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgVolume.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgWidget.cmake)
include(${THIS_MODULE_PATH}/find_module/osg/FindosgQT.cmake)