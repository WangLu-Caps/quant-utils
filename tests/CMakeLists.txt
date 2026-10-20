add_executable(test_indicators test_indicators.cpp)
target_link_libraries(test_indicators PRIVATE quant GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_indicators)
