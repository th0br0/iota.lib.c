cmake_minimum_required(VERSION 3.1.0)

project(iota.lib.c)
enable_language(C CXX)

include(CTest)

# Global definitions
set(CMAKE_PROJECT_NAME "iota.lib.c")
set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/CMake/Modules
  ${CMAKE_SOURCE_DIR}/external/sanitizers-cmake/cmake
  )
set(CMAKE_C_FLAGS -Wall)
set(LIBRARY_NAME "IOTA")

# Package dependencies
find_package(Sanitizers REQUIRED)
include(SetupCCurl)

# Generic output
message(STATUS "Host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "Current build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Current build type flags: ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")

# Includes
include_directories(
  ${CMAKE_SOURCE_DIR}/include/
  )

# Library source
file(GLOB_RECURSE LIB_SRC src/*.c) 
add_library(${LIBRARY_NAME}static STATIC ${LIB_SRC})
target_link_libraries(${LIBRARY_NAME}static ccurl)

if(DEFINED BUILD_SHARED)
  add_library(${LIBRARY_NAME} SHARED ${LIB_SRC})
  set_property(TARGET ${LIBRARY_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
  target_link_libraries(${LIBRARY_NAME} ccurl)
endif(DEFINED BUILD_SHARED)

# Testing
if(BUILD_TESTING) 
  include(SetupGTest)
  enable_testing()
  add_subdirectory(test)
endif(BUILD_TESTING)
