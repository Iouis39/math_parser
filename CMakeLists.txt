cmake_minimum_required(VERSION 3.13)
set(project_name math_parser)

project(${project_name})

set(CMAKE_CXX_STANDARD 20)

find_package(doctest REQUIRED)
if(doctest_FOUND)
    message(STATUS "Found doctest")
else()
    message(FATAL_ERROR "Could not find doctest")
endif()

## lib

add_library(${project_name}-lib
        src/characterType.cpp
        src/LexicalAnalyzer.cpp
        )

target_link_libraries(${project_name}-lib
        PUBLIC doctest::doctest
        )

target_include_directories(${project_name}-lib PUBLIC src)

## main binary

add_executable(${project_name}-bin
        src/main.cpp
        )

target_link_libraries(${project_name}-bin ${project_name}-lib)
add_dependencies(${project_name}-bin ${project_name}-lib)

## test binary

add_executable(${project_name}-test
        test/test.cpp
        )

target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

# general properties

set_target_properties(${project_name}-lib ${project_name}-bin ${project_name}-test PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        )

enable_testing()
add_test(project-tests ${project_name}-test)
