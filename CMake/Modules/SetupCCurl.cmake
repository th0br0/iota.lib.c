set(CCURL_ROOT external/ccurl/src CACHE STRING "CCurl source root")

message(STATUS "CCURL_ROOT is set to ${CCURL_ROOT}")

include_directories(${PROJECT_SOURCE_DIR}/${CCURL_ROOT}/lib)

set(CCURL_SOURCES
  ${PROJECT_SOURCE_DIR}/${CCURL_ROOT}/lib/util/converter.c
  ${PROJECT_SOURCE_DIR}/${CCURL_ROOT}/lib/exports.c
  ${PROJECT_SOURCE_DIR}/${CCURL_ROOT}/lib/curl.c
  )

add_library(ccurl ${CCURL_SOURCES})
set_property(TARGET ccurl PROPERTY POSITION_INDEPENDENT_CODE ON)
