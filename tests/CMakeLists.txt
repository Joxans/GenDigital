add_executable(GenDigitalTests LRUCacheTest.cpp)

target_link_libraries(GenDigitalTests PRIVATE gtest gtest_main LRUCache)

add_test(NAME GenDigitalTests COMMAND GenDigitalTests)