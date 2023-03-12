cmake_minimum_required(VERSION 3.21)
project(patterns)


set(CMAKE_CXX_STANDARD 14)

include_directories(
        include
)

add_library(
        ${PROJECT_NAME}
        src/misc/combinatorics.cpp
        src/misc/CombinatoricsData.cpp
        src/misc/PatternBuilder.cpp
        src/patternResolver.cpp
        src/fastPatternResolver.cpp
)

add_executable(CombinatoricsTest tests/combinatoricsTest.cpp)
target_link_libraries(CombinatoricsTest  ${PROJECT_NAME})
add_test(NAME CombinatoricsTest COMMAND CombinatoricsTest)

add_executable(PermutationResolverTest tests/permutationResolverTest.cpp)
target_link_libraries(PermutationResolverTest  ${PROJECT_NAME})
add_test(NAME PermutationResolverTest COMMAND PermutationResolverTest)

add_executable(PatternResolverTest tests/patternResolverTest.cpp)
target_link_libraries(PatternResolverTest  ${PROJECT_NAME})
add_test(NAME PatternResolverTest COMMAND PatternResolverTest)

add_executable(FastPatternResolverTest tests/fastPatternResolverTest.cpp)
target_link_libraries(FastPatternResolverTest  ${PROJECT_NAME})
add_test(NAME FastPatternResolverTest COMMAND FastPatternResolverTest)

add_executable(FastPatternResolver2Test tests/fastPatternResolver2Test.cpp)
target_link_libraries(FastPatternResolver2Test  ${PROJECT_NAME})
add_test(NAME FastPatternResolver2Test COMMAND FastPatternResolver2Test)


