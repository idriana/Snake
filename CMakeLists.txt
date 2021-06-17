cmake_minimum_required(VERSION 3.17)
project(cppprj)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppprj main.cpp)
add_subdirectory(doctest)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(cppprj ${SFML_LIBRARIES})

#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_custom_command(TARGET cppprj POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "../source/play_button.jpg"
        "../source/snake.jpg"
        "../source/wall.jpg"
        "../source/empty.jpg"
        "../source/apple.jpg"
        "$<TARGET_FILE_DIR:cppprj>"
        )