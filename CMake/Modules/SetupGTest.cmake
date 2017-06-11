set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")
set(GOOGLEMOCK_ROOT external/googletest/googlemock CACHE STRING "Google Mock source root")

message(STATUS "GOOGLETEST_ROOT set to ${GOOGLETEST_ROOT}")
message(STATUS "GOOGLEMOCK_ROOT set to ${GOOGLEMOCK_ROOT}")

# google test includes
include_directories(
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
    ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/include
    )

# google test sources
set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/src/gmock-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/src/gmock_main.cc
    )

add_library(googletest ${GOOGLETEST_SOURCES})
