cmake_minimum_required(VERSION 3.10)
project(myproject)

add_executable(myproject main.c player.c match.c)
target_link_libraries(myproject -lm)

configure_file(input.txt ${CMAKE_BINARY_DIR}/input.txt COPYONLY)
configure_file(names.txt ${CMAKE_BINARY_DIR}/names.txt COPYONLY)