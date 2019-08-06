cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wpedantic\;-Werror\;-Wall\;-Wextra>)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ntic_tac_toe)

file(GLOB SRC "src/*.cpp")

find_path(NCURSES_HEADERS ncurses.h)
find_library(NCURSES_LIB ncursesw)

include(cmake/StyleChecker.cmake)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${NCURSES_HEADERS})
target_link_libraries(${PROJECT_NAME} ${NCURSES_LIB})
