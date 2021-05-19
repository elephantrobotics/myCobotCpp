cmake_minimum_required(VERSION 3.19)
project(myCobotCppExample VERSION 0.1.0
    DESCRIPTION "C++ Interface for myCobot"
    LANGUAGES CXX
)

if("$ENV{QTDIR}" STREQUAL "")
    message(FATAL_ERROR "Please set env var QTDIR to Qt toolchain path")
endif()
find_program(QT_QMAKE_EXECUTABLE
    NAMES qmake
    PATHS "$ENV{QTDIR}/bin"
    REQUIRED
    NO_DEFAULT_PATH
)
set(QT_INSTALL_PREFIX "$ENV{QTDIR}")
execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} "-query" "QT_INSTALL_PLUGINS"
    OUTPUT_VARIABLE QT_INSTALL_PLUGINS
    ERROR_VARIABLE _stderr
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_PREFIX_PATH "${QT_INSTALL_PREFIX}")

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please run mkdir build; cd build; cmake ..")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(UNIX)
    # UNIX like, APPLE or CYGWIN
    add_compile_definitions(OS_UNIX)
endif()
if(WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # both 32-bit and 64-bit Windows
    add_compile_definitions(OS_WINDOWS)
endif()
if(APPLE)
    # macOS, iOS, tvOS, watchOS
    add_compile_definitions(OS_APPLE)
endif()
if(CYGWIN)
    add_compile_definitions(OS_CYGWIN)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(OS_LINUX)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_definitions(OS_MACOS)
endif()

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i[3456]86")
    add_compile_definitions(CPU_X86)
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    add_compile_definitions(CPU_X64)
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm.*")
    add_compile_definitions(CPU_ARM)
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
    add_compile_definitions(CPU_AARCH64)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
endif()
# Set the possible values of build type for cmake-gui
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(DEBUG)
else()
    add_compile_definitions(NDEBUG)
endif()

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# check for LTO (Link-Time Optimization)
#XXX: LTO on wingw windows is broken, even though it says it is supported
#TODO: add compiler detection (gcc, clang, msvc, mingw gcc, cygwin gcc)
if(NOT(WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
    include(CheckIPOSupported)
    check_ipo_supported(RESULT lto_supported OUTPUT lto_supported_output)
    if(lto_supported)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(WARNING "LTO is not supported: ${lto_supported_output}")
    endif()
else()
    message(WARNING "LTO is not supported on MinGW")
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    message(STATUS "Using ccache found: ${CCACHE_PROGRAM}")
endif()

include(CMakePrintHelpers)
include(CMakePrintSystemInformation)
include(CMakeDependentOption)

# Install
message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}")
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKEDIR CMake)
else()
    set(DEF_INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKEDIR ${DEF_INSTALL_CMAKEDIR} CACHE PATH "Installation directory for CMake files")
foreach(p LIB BIN INCLUDE CMAKE)
    file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_${p}DIR} _path)
    message(STATUS "Installing ${p} components to ${_path}")
    unset(_path)
endforeach()

# Generate folders for IDE targets (e.g., VisualStudio solutions)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(IDE_FOLDER "")

enable_testing()
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

##################
# Build Options
##################

if(WIN32)
    add_compile_definitions(_USE_MATH_DEFINES)
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

#######
# Qt
#######

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS SerialPort)

####################
# Target Settings
####################

add_executable(myCobotCppExample)
set_target_properties(myCobotCppExample
    PROPERTIES
        DEBUG_POSTFIX "_d"
        MACOSX_RPATH ON
)
target_sources(myCobotCppExample
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include/MyCobot.hpp
        ${CMAKE_CURRENT_LIST_DIR}/include/MyCobotExport.hpp
        ${CMAKE_CURRENT_LIST_DIR}/src/myCobotExample.cpp
)
target_compile_definitions(myCobotCppExample
    PRIVATE
        MYCOBOTCPP_DSO
)
target_include_directories(myCobotCppExample
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_BINARY_DIR}/generated
)
target_compile_options(myCobotCppExample PRIVATE
    -Wall
    -Wextra
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wlogical-op
    -Wdouble-promotion
    -Wformat=2
    -Werror=return-type
    -Werror=switch
    -Werror=switch-enum
    -Wundef
    -Wfloat-equal
    -Winit-self
    -Wunreachable-code
    -Wctor-dtor-privacy
    -Werror=shadow
    -Werror=switch-default
    -Werror=switch-unreachable
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wduplicated-branches
    -Wnull-dereference
    -Wno-useless-cast
    -Wno-expansion-to-defined
    -Weffc++
    -fexceptions
)
add_library(
    myCobotCpp
    SHARED
    IMPORTED
    GLOBAL
)
set_target_properties(myCobotCpp PROPERTIES
    IMPORTED_SONAME
        myCobotCpp
    IMPORTED_LOCATION
        ${CMAKE_CURRENT_LIST_DIR}/lib/libmyCobotCpp${CMAKE_SHARED_LIBRARY_SUFFIX}
    IMPORTED_IMPLIB
        ${CMAKE_CURRENT_LIST_DIR}/lib/libmyCobotCpp${CMAKE_IMPORT_LIBRARY_SUFFIX}
)
target_link_libraries(myCobotCppExample PRIVATE
    Qt5::Core
    Qt5::SerialPort
    myCobotCpp
)

install(
    TARGETS
        myCobotCppExample
    RUNTIME
        DESTINATION ${INSTALL_BINDIR}
        COMPONENT bin
    LIBRARY
        DESTINATION ${INSTALL_LIBDIR}
        COMPONENT lib
    ARCHIVE
        DESTINATION ${INSTALL_LIBDIR}
        COMPONENT lib
    INCLUDES
        DESTINATION ${INSTALL_INCLUDEDIR}/include/mycobot
    PUBLIC_HEADER
        DESTINATION ${INSTALL_INCLUDEDIR}/mycobot
        COMPONENT dev
    BUNDLE
        DESTINATION ${INSTALL_BINDIR}
)
