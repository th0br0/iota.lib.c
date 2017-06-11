file(GLOB TEST_SRC *.cc)
add_executable(runUnitTests ${TEST_SRC})
target_link_libraries(runUnitTests googletest pthread ${LIBRARY_NAME}static) 
target_compile_features(runUnitTests PRIVATE cxx_range_for)
add_sanitizers(runUnitTests)

add_test(AllTests runUnitTests)
