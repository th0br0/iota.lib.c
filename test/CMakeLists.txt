file(GLOB TEST_SRC *.cc)
add_executable(runUnitTests ${TEST_SRC})
target_link_libraries(runUnitTests googletest pthread ${LIBRARY_NAME}static) 
add_sanitizers(runUnitTests)

add_test(AllTests runUnitTests)
