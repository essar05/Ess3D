cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
set(CMAKE_VERBOSE_MAKEFILE ON)

PROJECT(Ess3D VERSION 0.0.1 LANGUAGES CXX)

################################################################################
# Set target arch type if empty.
################################################################################
IF (MSVC)
    IF (NOT CMAKE_VS_PLATFORM_NAME)
        SET(CMAKE_VS_PLATFORM_NAME "x64")
    ENDIF ()
    MESSAGE("${CMAKE_VS_PLATFORM_NAME} architecture in use")

    IF (NOT (("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64") OR ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")))
        MESSAGE(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
    ENDIF ()

    IF ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        SET(PLATFORM_ARCHITECTURE "Win64")
    ENDIF()
    IF ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        SET(PLATFORM_ARCHITECTURE "Win32")
    ENDIF()
ENDIF ()

IF (UNIX)
    SET(PLATFORM_ARCHITECTURE "x86_x64")
ENDIF()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(cmake/Utils.cmake)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

ADD_SUBDIRECTORY(source)