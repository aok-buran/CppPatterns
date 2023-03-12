cmake_minimum_required(VERSION 3.21)
project(App)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ../patterns/include
)

link_directories(
        patterns
)

add_executable(App app.cpp)
target_link_libraries(App patterns)

add_executable(GenStatistics genStatistic.cpp)
target_link_libraries(GenStatistics patterns)
