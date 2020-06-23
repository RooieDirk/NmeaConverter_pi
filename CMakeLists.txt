# ---------------------------------------------------------------------------
# Author:      jongough aka. Jon Gough Copyright: License:     wxWidgets License
# ---------------------------------------------------------------------------

set(CMLOC "CMakeLists: ")

cmake_minimum_required(VERSION 3.1.1)
if(COMMAND cmake_policy)
    if(POLICY CMP0043)
        cmake_policy(SET CMP0043 NEW)
    endif(POLICY CMP0043)
    cmake_policy(SET CMP0048 NEW)
    message(STATUS "${CMLOC}CMP0048 set to New")
    if(POLICY CMP0077)
        cmake_policy(SET CMP0077 NEW)
    endif(POLICY CMP0077)
endif(COMMAND cmake_policy)

set(VERBOSE_NAME "nmeaconverter")
set(COMMON_NAME "nmeaconverter_pi")
set(TITLE_NAME "OCPNNMEACONVERTER")
set(PACKAGE_CONTACT "RooieDirk")
set(PACKAGE "nmeaconverter_pi")

set(VERSION_MAJOR "1")
set(VERSION_MINOR "2")
set(VERSION_PATCH "0")
set(VERSION_TWEAK "2")
set(VERSION_DATE "19/06/2020")
set(OCPN_MIN_VERSION "ov50")
set(OCPN_API_VERSION_MAJOR "1")
set(OCPN_API_VERSION_MINOR "16")

message(STATUS "${CMLOC}PI Version: ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}")
message(STATUS "${CMLOC}OCPN API Verson: ${OCPN_API_VERSION_MAJOR}.${OCPN_API_VERSION_MINOR}")
message(STATUS "${CMLOC}OCPN Min Verson: ${OCPN_MIN_VERSION}")

set(PARENT "opencpn")

# The next line allows for setting up your own local webserver with git on it for testing purposes, the default is github.com
set(GIT_REPOSITORY_SERVER "github.com")

# Builds repository sufficies
set(PROD "prod") # Standard Repos
set(BETA "beta") # Standard Repos
set(ALPHA "alpha") # Standard Repos

set(CLOUDSMITH_USER "dirk-smits")
# set this if your cloudsmith repository name does not match your git repository name set(CLOUDSMITH_BASE_REPOSITORY "${GIT_REPOSITORY_NAME}")
set(XML_INFO_URL "https://opencpn.org/OpenCPN/plugins/nmeaconvert.html")
set(XML_SUMMARY "Plugin to change and cherrypich from other NMEA sentences")
set(XML_DESCRIPTION "NmeaConverter is a plugin where you can manipulate or add new nmea sentences. It is rather tricky and easy to make mistakes that will 'hang' OpenCPN, but if used right very powerfull")

#
# ----- Modify section above to include all the details for your plugin ----- ##
#

#
# ----- Modify section below if there are special requirements for the plugin ----- ##
#

option(PLUGIN_USE_SVG "Use SVG graphics" ON)

set(CMAKE_CXX_STANDARD 11)

# Use local version of GLU library
set(USE_LOCAL_GLU TRUE)
# Prefer libGL.so to libOpenGL.so, see CMP0072
set(OpenGL_GL_PREFERENCE "LEGACY")
option(USE_GL "Enable OpenGL support" ON)
message(STATUS "${CMLOC}USE_GL: ${USE_GL}")

set(BUNDLE_DATA FALSE)
set(CMAKE_BUILD_TYPE
    "Release"
    CACHE STRING "Choose the type of build")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "None" "Debug" "Release" "RelWithDebInfo" "MinSizeRel")

message(STATUS "${CMLOC}Build type: ${CMAKE_BUILD_TYPE}")

##
## ----- The statements below are used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
##

project(${PACKAGE})

include("cmake/PluginSetup.cmake")

set(CMAKE_VERBOSE_MAKEFILE ON)

option(Plugin_CXX11 "Use c++11" ON)

#
# ----- Modify section above if there are special requirements for the plugin ----- ##
#

include("cmake/PluginConfigure.cmake")

#
# ----- Change below to match project requirements ----- ##
#

add_definitions(-DUSE_S57)

set(SRCS
    src/icons.h
        src/icons.cpp
        src/NmeaConverter_pi.h
        src/NmeaConverter_pi.cpp
        src/ec_defs.h
        src/ec_engine.h
        src/ec_engine.cpp)

set(HDRS
    )

set(OCPNSRC
    )
set(OCPNHDRS
    ocpninclude/AISTargetAlertDialog.h
    ocpninclude/AISTargetQueryDialog.h
    ocpninclude/bbox.h
    ocpninclude/cutil.h
    ocpninclude/geodesic.h
    ocpninclude/georef.h
    ocpninclude/Hyperlink.h
    ocpninclude/ocpn_plugin.h
    ocpninclude/SelectItem.h
    ocpninclude/TexFont.h
    ocpninclude/timers.h
    ocpninclude/vector2D.h
    ocpninclude/wx28compat.h
    ocpninclude/GL/gl.h
    ocpninclude/GL/glext.h
    ocpninclude/GL/gl_private.h
    ocpninclude/GL/glu.h
    ocpninclude/wx/json_defs.h
    ocpninclude/wx/jsonreader.h
    ocpninclude/wx/jsonval.h
    ocpninclude/wx/jsonwriter.h)

# set(EXTSRC ${EXTSRC} extsrc/clipper.cpp extsrc/pugixml.cpp)
# 
# set(EXTINCLUDE ${EXTINCLUDE} extinclude/clipper.hpp extinclude/pugiconfig.hpp extinclude/pugixml.hpp)

# if(APPLE)
#     option(OD_JSON_SCHEMA_VALIDATOR "Use JSON Schema validator" OFF)
# else(APPLE)
#     option(OD_JSON_SCHEMA_VALIDATOR "Use JSON Schema validator" ON)
# endif(APPLE)
# 
# if(OD_JSON_SCHEMA_VALIDATOR)
#     message(STATUS "${CMLOC}Using JSON Schema validation - warning this changes the 'flavour' of the executable and it may not be compatible with OpenCPN")
#     add_definitions(-DOD_JSON_SCHEMA_VALIDATOR)
#     message(STATUS "${CMLOC}Adding JSON Schema validation")
# 
#     set(EXTSRC ${EXTSRC} extsrc/json-schema-validator/json-schema-draft7.json.cpp extsrc/json-schema-validator/json-uri.cpp extsrc/json-schema-validator/json-validator.cpp)
#     set(EXTINCLUDE ${EXTINCLUDE} extinclude/nlohmann/json.hpp extinclude/json-schema-validator/json-schema.hpp)
#     include_directories(BEFORE ${PROJECT_SOURCE_DIR}/extinclude/json-schema-validator)
# else(OD_JSON_SCHEMA_VALIDATOR)
#     message(STATUS "${CMLOC}Not using JSON Schema validation - warning invalid JSON 'may' cause unexpected crashes")
# endif(OD_JSON_SCHEMA_VALIDATOR)

option(OD_USE_SVG "Use SVG graphics" ON)

if(OD_USE_SVG)
    message(STATUS "${CMLOC}SVG support enabled...")
    if(NOT QT_ANDROID)

        add_definitions(-DODraw_USE_SVG)
    endif(NOT QT_ANDROID)
endif(OD_USE_SVG)

if(OCPN_MIN_VERSION)
    message(STATUS "${CMLOC}Using O5 MUI")
    if(NOT QT_ANDROID)
        add_definitions(-DODraw_USE_MUI)
    endif(NOT QT_ANDROID)
endif(OCPN_MIN_VERSION)

# include_directories(BEFORE ${PROJECT_SOURCE_DIR}/extsrc/mygdal)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpnsrc/glu/include)
# include_directories(BEFORE ${PROJECT_SOURCE_DIR}/extinclude)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude/wxcurl)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude/wxcurl/include)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude/GL)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpnsrc/lz4)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpnsrc/bitmaps)

if(UNIX)
    include("cmake/FindTinyXML.cmake")
    find_package(TinyXML QUIET)
endif(UNIX)

if(TINYXML_FOUND)
    message(STATUS "Building with system tinyxml")
    include_directories(${TINYXML_INCLUDE_DIR})
    add_library(${PACKAGE_NAME} SHARED ${SRCS} ${HDRS} ${OCPNSRC} ${EXTSRC})
    target_link_libraries(${PACKAGE_NAME} ${TINYXML_LIBRARIES})
else(TINYXML_FOUND)
    message(STATUS "Building with embedded tinyxml")
    include_directories(extsrc/tinyxml/)
    set(SRC_LTINYXML extsrc/tinyxml/tinyxml.cpp extsrc/tinyxml/tinyxmlparser.cpp extsrc/tinyxml/tinyxmlerror.cpp)
    add_library(${PACKAGE_NAME} SHARED ${SRCS} ${HDRS} ${OCPNSRC} ${EXTSRC} ${SRC_LTINYXML})
endif(TINYXML_FOUND)

add_definitions(-DTIXML_USE_STL)

if(UNIX AND NOT APPLE)
    if(OD_JSON_SCHEMA_VALIDATOR)
        # Change OS/ABI to be UNIX - System V to make it run with OCPN
        set(lib_name lib${PACKAGE_NAME}.so)
        message(STATUS "${CMLOC}lib-name: ${lib_name}")
        find_file(elfedit elfedit)
        if(NOT (${elfedit} STREQUAL "elfedit-NOTFOUND"))
            message(STATUS "${CMLOC}Will ensure OS/ABI is set to 0 to match OCPN")
            add_custom_command(
                TARGET ${PACKAGE_NAME}
                POST_BUILD
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                DEPENDS ${PACKAGE_NAME}
                COMMENT " Running post build action on ${lib_name}."
                COMMAND sh -c 'elfedit --input-osabi=Linux --output-osabi=none ${lib_name} || (echo 0) ')
        else(NOT (${elfedit} STREQUAL "elfedit-NOTFOUND"))
            message(STATUS "${CMLOC}Cannot correct OS/ABI to match OCPN if it is generated incorrectly. Package binutils needed")
        endif(NOT (${elfedit} STREQUAL "elfedit-NOTFOUND"))
    endif(OD_JSON_SCHEMA_VALIDATOR)
endif(UNIX AND NOT APPLE)

get_property(
    dirs
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    message(STATUS "${CMLOC}dir='${dir}'")
endforeach()

#
# ----- Change above to match project requirements ----- ##
#

#
# ----- do not change - needed to build app ----- ##
#

include("cmake/PluginInstall.cmake")
include("cmake/PluginLocalization.cmake")
include("cmake/PluginPackage.cmake")
