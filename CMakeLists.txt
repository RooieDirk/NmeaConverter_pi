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

