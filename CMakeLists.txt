cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ntic_tac_toe)

add_compile_options(-Wall
    $<$<COMPILE_LANGUAGE:CXX>:-Wpedantic\;-Werror\;-Wextra\;-Wdouble-promotion>
)

# file(GLOB SRC "src/*.cpp")

find_path(NCURSES_HEADERS ncurses.h)
find_library(NCURSES_LIB ncursesw)

include(cmake/StyleChecker.cmake)

add_executable(${PROJECT_NAME} src/main.cpp)

file(GLOB SRC src/*.cpp)
add_library(${PROJECT_NAME}-lib ${SRC})

target_include_directories(${PROJECT_NAME}-lib PUBLIC ${NCURSES_HEADERS} include)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib ${NCURSES_LIB})
