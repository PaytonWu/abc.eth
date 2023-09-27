find_package(GTest REQUIRED)
include(GoogleTest)

aux_source_directory(./ ABC_ETH_TEST_SOURCES)

add_executable(tests ${ABC_ETH_TEST_SOURCES})
add_dependencies(tests ${ABC_ETH_LIBRARY} abc)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_directories(tests PRIVATE ${PROJECT_BINARY_DIR})
target_link_libraries(tests PRIVATE ${ABC_ETH_LIBRARY} abc GTest::GTest GTest::Main)

gtest_discover_tests(tests)