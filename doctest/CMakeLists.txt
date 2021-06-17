cmake_minimum_required(VERSION 3.17)
project(doctest)

set(CMAKE_CXX_STANDARD 17)

add_executable(tests ../tests_main.cpp)

add_library(doctest STATIC doctest.cpp)
# depend on some obvious c++11 features so the dependency is transitively added dependents
target_include_directories(doctest PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)
set_target_properties(doctest PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

add_library(doctest::doctest ALIAS doctest)
add_library(Catch2::Catch2 ALIAS doctest)
