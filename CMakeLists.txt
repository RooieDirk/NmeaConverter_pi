##---------------------------------------------------------------------------
## Author:      Pavel Kalian
## Copyright:   2014
## License:     GPLv2 License
##---------------------------------------------------------------------------

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(nmeaconverter_pi)

SET(PACKAGE_NAME nmeaconverter_pi)
SET(VERBOSE_NAME NmeaConverter)
SET(TITLE_NAME NmeaConverter)
SET(CPACK_PACKAGE_CONTACT "RooieDirk")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")

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
