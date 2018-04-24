#---------------------------------------------------------------------------
# Author:      Dirk Smits
# Copyright:   2018
# License:     GPLv3 License
#---------------------------------------------------------------------------

#define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

PROJECT(nmeaconverter_pi)

SET(PACKAGE_NAME nmeaconverter_pi)
SET(VERBOSE_NAME NmeaConverter)
SET(TITLE_NAME NmeaConverter)
SET(CPACK_PACKAGE_CONTACT "RooieDirk")

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")

#SET(CMAKE_BUILD_TYPE Debug)

# Definitions
add_definitions (
-D_FILE_OFFSET_BITS=64
-D_LARGEFILE_SOURCE
-DLIBUNRAR_BUILD
-DRARDLL
-DUNRAR
-DSILENT
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

INCLUDE("cmake/PluginConfigure.cmake")

SET(SRC_NMEATRANSLATOR
        src/NmeaConverter_pi.h
        src/NmeaConverter_pi.cpp
        src/ec_defs.h
        src/ec_engine.h
        src/ec_engine.cpp               
        )


ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_NMEATRANSLATOR})

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")

#**************************************************************************************************
# define minimum cmake version
# CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)
# # This should be 2.8.0 to have FindGTK2 module
# IF (COMMAND cmake_policy)
#  CMAKE_POLICY(SET CMP0003 OLD)
#  CMAKE_POLICY(SET CMP0005 OLD)
#  CMAKE_POLICY(SET CMP0011 OLD)
# ENDIF (COMMAND cmake_policy)
# 
# PROJECT(NmeaConverter_pi)
# 
# SET(PACKAGE_NAME NmeaConverter_pi)
# SET(PLUGIN_SOURCE_DIR .)
# MESSAGE (STATUS "*** Building ${PACKAGE_NAME} ***")
# #SET(CMAKE_BUILD_TYPE Debug)
# 
# IF (PREFIX)
#  SET(CMAKE_INSTALL_PREFIX ${PREFIX})
# ENDIF (PREFIX)
# 
# SET(PARENT opencpn)
# SET(PREFIX_BIN bin)
# SET(PREFIX_INCLUDE include)
# SET(PREFIX_DATA share)
# SET(PREFIX_PARENTDATA ${PREFIX_DATA}/${PARENT})
# 
# INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/src)
# 
# # require proper c++
# #ADD_DEFINITIONS( "-Wall -ansi -pedantic -Wno-variadic-macros" )
# #TODO: Should we use -fno-stack-protector
# # IF NOT DEBUGGING CFLAGS="-O2 -march=native"
# IF(NOT WIN32)
#  ADD_DEFINITIONS( "-Wall -g -fexceptions -fvisibility=hidden" )
# 
#  IF(NOT APPLE)
#  SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,-Bsymbolic")
#  ELSE(NOT APPLE)
#  SET(CMAKE_SHARED_LINKER_FLAGS "-Wl")
#  ENDIF(NOT APPLE)
# 
# ENDIF(NOT WIN32)
# 
# # Add some definitions to satisfy MS
# IF(WIN32)
#  ADD_DEFINITIONS(-D__MSVC__)
#  ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_DEPRECATE)
# ENDIF(WIN32)
# 
# 
# SET(wxWidgets_USE_LIBS base core net xml html adv)
# SET(BUILD_SHARED_LIBS TRUE)
# FIND_PACKAGE(wxWidgets REQUIRED)
# 
# INCLUDE(${wxWidgets_USE_FILE})
# 
# FIND_PACKAGE(Gettext REQUIRED)
# 
# # For convenience we define the sources as a variable. You can add
# # header files and cpp/c files and CMake will sort them out
# 
# 
# SET(SRC_NMEATRANSLATOR
#  src/NmeaConverter_pi.h
#  src/NmeaConverter_pi.cpp
#  src/ec_defs.h
#  src/ec_engine.h
#  src/ec_engine.cpp
#  )
# 
# 
# ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_NMEATRANSLATOR} )
# 
# IF(WIN32)
#  SET(OPENCPN_IMPORT_LIB "../../../${CMAKE_CFG_INTDIR}/${PARENT}")
#  TARGET_LINK_LIBRARIES( ${PACKAGE_NAME} ${OPENCPN_IMPORT_LIB} )
#  ADD_DEPENDENCIES(${PACKAGE_NAME} ${PARENT})
# ENDIF(WIN32)
# 
# TARGET_LINK_LIBRARIES( ${PACKAGE_NAME} ${wxWidgets_LIBRARIES} )
# 
# IF(UNIX)
# INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME LIBRARY DESTINATION ${PREFIX_PARENTDATA}/plugins)
# ENDIF(UNIX)
# 
# IF(WIN32)
# INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME DESTINATION "plugins")
# ENDIF(WIN32)
#  
# 
# # define minimum cmake version
# CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)
# # This should be 2.8.0 to have FindGTK2 module
# IF (COMMAND cmake_policy)
#  CMAKE_POLICY(SET CMP0003 OLD)
#  CMAKE_POLICY(SET CMP0005 OLD)
#  CMAKE_POLICY(SET CMP0011 OLD)
# ENDIF (COMMAND cmake_policy)
# 
# PROJECT(NmeaConvertor_pi)
# 
# SET(PACKAGE_NAME NmeaConvertor_pi)
# SET(PLUGIN_SOURCE_DIR ..)
# MESSAGE (STATUS "*** Building ${PACKAGE_NAME} ***")
# 
# #SET(CMAKE_BUILD_TYPE Debug)
# 
# IF (PREFIX)
#  SET(CMAKE_INSTALL_PREFIX ${PREFIX})
# ENDIF (PREFIX)
# 
# SET(PARENT opencpn)
# SET(PREFIX_BIN bin)
# SET(PREFIX_INCLUDE include)
# SET(PREFIX_DATA share)
# SET(PREFIX_PARENTDATA ${PREFIX_DATA}/${PARENT})
# 
# INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
# 
# # require proper c++
# #ADD_DEFINITIONS( "-Wall -ansi -pedantic -Wno-variadic-macros" )
# #TODO: Should we use -fno-stack-protector
# # IF NOT DEBUGGING CFLAGS="-O2 -march=native"
# IF(NOT WIN32)
#  ADD_DEFINITIONS( "-Wall -g -fexceptions -fvisibility=hidden" )
# 
#  IF(NOT APPLE)
#  SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,-Bsymbolic")
#  ELSE(NOT APPLE)
#  SET(CMAKE_SHARED_LINKER_FLAGS "-Wl")
#  ENDIF(NOT APPLE)
# 
# ENDIF(NOT WIN32)
# 
# # Add some definitions to satisfy MS
# IF(WIN32)
#  ADD_DEFINITIONS(-D__MSVC__)
#  ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_DEPRECATE)
# ENDIF(WIN32)
# 
# 
# SET(wxWidgets_USE_LIBS base core net xml html adv)
# SET(BUILD_SHARED_LIBS TRUE)
# FIND_PACKAGE(wxWidgets REQUIRED)
# 
# INCLUDE(${wxWidgets_USE_FILE})
# 
# FIND_PACKAGE(Gettext REQUIRED)
# 
# # For convenience we define the sources as a variable. You can add
# # header files and cpp/c files and CMake will sort them out
# 
# 
# SET(SRC_NMEACONVERTOR
#   src/NmeaConverter_pi.h
#   src/NmeaConverter_pi.cpp
#   src/ec_defs.h
#   src/ec_engine.h
#   src/ec_engine.cpp
#  )
# 
# 
# ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_NMEACONVERTOR} )
# 
# IF(WIN32)
#  SET(OPENCPN_IMPORT_LIB "../../../${CMAKE_CFG_INTDIR}/${PARENT}")
#  TARGET_LINK_LIBRARIES( ${PACKAGE_NAME} ${OPENCPN_IMPORT_LIB} )
#  ADD_DEPENDENCIES(${PACKAGE_NAME} ${PARENT})
# ENDIF(WIN32)
# 
# TARGET_LINK_LIBRARIES( ${PACKAGE_NAME} ${wxWidgets_LIBRARIES} )
# 
# IF(UNIX)
# INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME LIBRARY DESTINATION ${PREFIX_PARENTDATA}/plugins)
# ENDIF(UNIX)
# 
# IF(WIN32)
# INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME DESTINATION "plugins")
# ENDIF(WIN32)
