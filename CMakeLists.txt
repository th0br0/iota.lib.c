cmake_minimum_required(VERSION 3.4.0)

project(iota.lib.c)
enable_language(C CXX)

# Global definitions
set(CMAKE_PROJECT_NAME "iota.lib.c")
set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/CMake/Modules
  ${CMAKE_SOURCE_DIR}/external/sanitizers-cmake/cmake
  )
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
file(GLOB LIB_SRC src/**.c) 
add_library(${LIBRARY_NAME}static STATIC ${LIB_SRC})
target_link_libraries(${LIBRARY_NAME}static ccurl)

if(DEFINED ${BUILD_SHARED})
  add_library(${LIBRARY_NAME} SHARED ${LIB_SRC})
  target_link_libraries(${LIBRARY_NAME} ccurl)
endif(DEFINED ${BUILD_SHARED})

# Testing
if(DEFINED ${BUILD_TEST}) 
  include(CTest)
  include(SetupGTest)
  enable_testing()

  add_subdirectory(test)
endif(DEFINED ${BUILD_TEST})
