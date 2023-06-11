# ---------------------------------------------------------------------------
# Frontend2 Author:      jongough aka. Jon Gough Copyright: License:     wxWidgets License
# ---------------------------------------------------------------------------

## ----- When changing this file do NOT change the order in which sections occur        ----- ##
## ----- Changes should only be made between the section blocks that identify where     ----- ##
## ----- these changes should be. The whole configuration process relies on this        ----- ##
## ----- sequence to be successful                                                      ----- ##
##
#-----------------------------------------------------------------------------
# CI-CMake: v1.0.238.0 09/06/2023  # DD/MM/YYYY format  CI-CMake Author: Jon Gough
# ---------------------------------------------------------------------------
## buildCI:yes useODAPI:no validateJSON:no


##
## ----- Modify section below to include all the details for your plugin ----- ##
##

set(CMLOC "CMakeLists: ")

# define minimum cmake version
cmake_minimum_required(VERSION 3.5.1)
if(COMMAND cmake_policy)
    if(POLICY CMP0043)
        cmake_policy(SET CMP0043 NEW)
    endif(POLICY CMP0043)
    cmake_policy(SET CMP0048 NEW)
# Need cmake 3.13 to implement this, but raspbian builds are at 3.7.2 and bionic at 3.10 and xenial builds at 3.5.1
#    cmake_policy(SET CMP0076 NEW)
    if(POLICY CMP0077)
        cmake_policy(SET CMP0077 NEW)
    endif(POLICY CMP0077)
endif(COMMAND cmake_policy)

# define plugin name, owner and versions
set(VERBOSE_NAME "nmeaconverter")
set(COMMON_NAME "NmeaConverter_pi")
set(TITLE_NAME "OCPNNMEACONVERTER")
set(PACKAGE_CONTACT "RooieDirk")
set(PACKAGE "nmeaconverter_pi")

set(VERSION_MAJOR "1")
set(VERSION_MINOR "3")
set(VERSION_PATCH "3")
set(VERSION_TWEAK "0")
set(VERSION_DATE "11/06/2023")
set(OCPN_MIN_VERSION "ov58")
set(OCPN_API_VERSION_MAJOR "1")
set(OCPN_API_VERSION_MINOR "16")
set(TP_COMMENT "  * Release for O571 using CI")

set(PARENT "opencpn")

# The next line allows for setting up your own local webserver with git on it for testing purposes, the default is github.com
#set(GIT_REPOSITORY_SERVER "github.com")

# Specifies cloudsmith repository sufficies
set(PROD "prod")    # Standard Repos
set(BETA "beta")    # Standard Repos
set(ALPHA "alpha")  # Standard Repos

# set this if your cloudsmith repository name does not match your git repository name
#set(CLOUDSMITH_BASE_REPOSITORY "testplugin_pi")
set(CLOUDSMITH_BASE_REPOSITORY "nmeaconverter")
# Set the following to use OpenCPN cloudsmith repositories instead of own repositories
set(CLOUDSMITH_USER "opencpn")
#set(CLOUDSMITH_USER "jon-gough")
#set(CLOUDSMITH_USER "dirk-smits")

# set this if your cloudsmith repository name does not match your git repository name set(CLOUDSMITH_BASE_REPOSITORY "${GIT_REPOSITORY_NAME}")
set(XML_INFO_URL "https://opencpn.org/OpenCPN/plugins/nmeaconvert.html")
set(XML_SUMMARY "Plugin to change and cherrypich from other NMEA sentences")
set(XML_DESCRIPTION "NmeaConverter is a plugin where you can manipulate or add new nmea sentences. It is rather tricky and easy to make mistakes that will 'hang' OpenCPN, but if used right very powerfull")

##
## ----- Modify section above to include all the details for your plugin ----- ##
##

##
## ----- Modify section below if there are special requirements for the plugin ----- ##
##

option(PLUGIN_USE_SVG "Use SVG graphics" ON)

set(CMAKE_CXX_STANDARD 11)

# Use local version of GLU library
# requires libs/glu directory
set(USE_LOCAL_GLU TRUE)
# Prefer libGL.so to libOpenGL.so, see CMP0072
set(OpenGL_GL_PREFERENCE "LEGACY")

option(USE_GL "Enable OpenGL support" ON)
message(STATUS "${CMLOC}USE_GL: ${USE_GL}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "" "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
message(STATUS "${CMLOC}Build type: ${CMAKE_BUILD_TYPE}")

##
## ----- The statements below are used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
##

project(${PACKAGE})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include("PluginSetup")

##
## ----- The above is used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
##

##
## ----- Modify section below if there are special requirements for the plugin ----- ##
##

set(CMAKE_VERBOSE_MAKEFILE "Activate verbose mode for make files" ON)

option(Plugin_CXX11 "Use c++11" OFF)

##
## ----- Modify section above if there are special requirements for the plugin ----- ##
##

##
## ----- do not change next section - needed to configure build process ----- ##
##

include("PluginConfigure")

##
## ----- do not change section above - needed to configure build process ----- ##
##

#
# ----- Change below to match project requirements for source, headers, etc. ----- ##
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

set(LIBSSRC libs/wxJSON/src/jsonreader.cpp libs/wxJSON/src/jsonval.cpp libs/wxJSON/src/jsonwriter.cpp)

set(LIBHDRS
    libs/GL/gl.h
    libs/GL/gl_private.h
    libs/GL/glext.h
    libs/GL/glu.h
    libs/wxJSON/include/json_defs.h
    libs/wxJSON/include/jsonreader.h
    libs/wxJSON/include/jsonval.h
    libs/wxJSON/include/jsonwriter.h)

add_definitions(-DPLUGIN_USE_SVG)

set(EXTINCLUDE_DIR ${EXTINCLUDE_DIR} extinclude libs/ocpn-api/)

#
# ----- If using JSON validation in plugin section below is needed ----- ##
#

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

#
# ----- If using JSON validation in plugin section above is needed ----- ##
#

option(OD_USE_SVG "Use SVG graphics" ON)
# include_directories(BEFORE ${PROJECT_SOURCE_DIR}/extsrc/mygdal)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpnsrc/glu/include)
# include_directories(BEFORE ${PROJECT_SOURCE_DIR}/extinclude)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude/wxcurl)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude/wxcurl/include)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude/GL)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpnsrc/lz4)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpnsrc/bitmaps)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/${EXTINCLUDE_DIR})
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/GL)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/ocpn-api)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/wxJSON/include)

#
# ----- Change below to match project requirements for android build ----- ##
#

if(QT_ANDROID)
    include_directories( ${PROJECT_SOURCE_DIR}/extinclude/GLES2)
endif(QT_ANDROID)

##
## ----- Change above to match project requirements for android build ----- ##
##


target_sources(${PACKAGE_NAME} PUBLIC ${SRCS} ${HDRS} ${OCPNSRC} ${EXTSRC} ${LIBSSRC})

if(NOT OCPN_FLATPAK_CONFIG)
    # Build environment not available when flatpak is being configured so following statements will not work
    message(STATUS "${CMLOC}Adding target link libraries to ${PACKAGE_NAME}")

    add_subdirectory(libs/tinyxml)

    target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)
endif(NOT OCPN_FLATPAK_CONFIG)

add_definitions(-DTIXML_USE_STL)

#
# ----- If using JSON validation in plugin section below is needed ----- ##
#

if(UNIX AND NOT APPLE AND NOT QT_ANDRIOD)
    if(PI_JSON_SCHEMA_VALIDATOR)
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
    endif(PI_JSON_SCHEMA_VALIDATOR)
endif(UNIX AND NOT APPLE AND NOT QT_ANDRIOD)

#
# ----- If using JSON validation in plugin section above is needed ----- ##
#

##
## ----- Change above to match project requirements ----- ##
##

##
## ----- do not change next section - needed to configure build process ----- ##
##

# Needed for android builds
if(QT_ANDROID)
    include_directories(BEFORE ${qt_android_include})
endif(QT_ANDROID)

# Needed for all builds
include("PluginInstall")
include("PluginLocalization")
include("PluginPackage")

##
## ----- do not change section above - needed to configure build process ----- ##
##
message(STATUS "${CMLOC}include directories: ")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    message(STATUS "${CMLOC}dir='${dir}'")
endforeach()
