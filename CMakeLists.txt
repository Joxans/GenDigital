cmake_minimum_required(VERSION 3.26)
project(GenDigital)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

add_library(LRUCache LRUCache.cpp)
add_executable(GenDigital main.cpp)

target_include_directories(GenDigital PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GenDigital PRIVATE LRUCache)


# tests
add_subdirectory(tests)

# add Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(GenDigitalTests PRIVATE gtest gtest_main LRUCache)