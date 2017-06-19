file(GLOB TEST_SRC *.cc)
add_executable(runUnitTests ${TEST_SRC})
target_link_libraries(runUnitTests googletest pthread ${LIBRARY_NAME}static) 
target_compile_features(runUnitTests PRIVATE cxx_range_for)
add_sanitizers(runUnitTests)

add_test(AllTests runUnitTests)

if(CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  target_link_libraries(runUnitTests gcov)
  target_compile_options(runUnitTests PRIVATE "-fprofile-arcs" "-ftest-coverage")
  target_compile_options(${LIBRARY_NAME}static PRIVATE "-fprofile-arcs" "-ftest-coverage")
  setup_target_for_coverage(coverage runUnitTests coverage)
endif(CMAKE_COMPILER_IS_GNUCXX) 

